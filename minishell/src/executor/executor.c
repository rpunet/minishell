/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/06 22:37:00 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_ast_node *cmd_node, int in, int out, char ***envp, int *fds)
{
	int			i;
	do_nothing(fds);

	char		**args;
	t_ast_node	*curr;
	pid_t		pid;

	if (cmd_node != NULL || cmd_node->type == CMDNAME_NODE)
	{
		curr = cmd_node;
		i = 0;
		while (curr != NULL && \
			(curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
		{
			i++;
			curr = curr->right;
		}
		args = malloc(sizeof(char *) * (i + 1));
		if (args == NULL)
			exit_program(NULL, 0, 0, "CMD Malloc is NULL");
		curr = cmd_node;
		i = 0;
		while (curr != NULL && \
			(curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
		{
			args[i] = ft_strdup(curr->data);
			// expand_vars(&args[i]);
			curr = curr->right;
			i++;
		}
		args[i] = NULL;
		if (i > 0)			//	if (!check_builtin())  ...
		{
			if (!ft_strcmp(args[0], "pwd"))
			{
				int save = dup(STDOUT_FILENO);

				if (out == 1)
					ft_pwd(args, *envp);
				else
				{
					dup2(out, STDOUT_FILENO);
					close(out);
					ft_pwd(args, *envp);
					dup2(save, STDOUT_FILENO);
					close(save);
				}
			}
			else if (!ft_strcmp(args[0], "echo"))
			{
				int save = dup(STDOUT_FILENO);

				if (out == 1)
					ft_echo(args, *envp);
				else
				{
					dup2(out, STDOUT_FILENO);
					close(out);
					ft_echo(args, *envp);
					dup2(save, STDOUT_FILENO);
					close(save);
				}					 // dup2 y close, copiar fds, como en pwd y export
			}

			else if (!ft_strcmp(args[0], "exit"))			//	EXIT TMB TIENE QUE IR EN PARENT
			{
				ft_exit();
			}
			else if (!ft_strcmp(args[0], "cd"))			// EN PÀRENT... ALGUNO MAŚ?
			{
				if (in == STDIN_FILENO && out == STDOUT_FILENO)
					ft_cd(args, envp);
			}
			else if (!ft_strcmp(args[0], "export"))
			{
				int save = dup(STDOUT_FILENO);

				if (out == 1)
					ft_export(args, envp);
				else
				{
					dup2(out, STDOUT_FILENO);
					close(out);
					ft_export(args, envp);
					dup2(save, STDOUT_FILENO);
					close(save);
				}
			}
			else if (!ft_strcmp(args[0], "unset"))
				ft_unset(&args[1], envp);
			else if (!ft_strcmp(args[0], "minishell"))
				execve("./minishell", args, *envp);

			// {											// o repetir esto o el ELSE de abajo
			// 	free_char_array(args, i);
			// 	return ;
			// }
			else
			{
				pid = fork();
				if (pid == 0)
				{
					if (in != 0)
					{
						dup2(in, STDIN_FILENO);
						close(in);
					}
					if (out != 1)
					{
						close(fds[READ]);						// este es el que hace que se cierre 	"top | echo hola"
						dup2(out, STDOUT_FILENO);
						close(out);
					}
	/*				if (check_builtins(args, *envp))			// al sacar los builtins de aqui, hay que añadir los fds a los argumentos de las funciones ft_pwd y ft_echo, para poder copiarles las las entradas/salidas a los pipes
					{
						free_char_array(args, i);
						// ft_putstr_fd("vemos esto aqui\n", 1);
						exit(0);
					}
	*/				if (exec_process(args, *envp, i) == -1)
					{
						free_char_array(args, i);
						exit_program(NULL, 0, 0, "Error de execve");   // salir sin mensaje, o devolver distintos errores para distinos mensajes
					}
				}
				else if (pid < 0)
				{
					free_char_array(args, i);
					exit_program(NULL, 0, 0, "CMD PID < 0");
				}
			}
		}
		free_char_array(args, i);
	}
}

int		exec_process(char **args, char **envp, int i)
{
	char	*directory;
	char	*path;
	DIR		*dir;

	directory = find_directory(&dir, args);  // pasa como &dir (**DIR) porque no esta inicializado
	if (!directory)
	{
		ft_printf("%s: Command nottttttt found\n", args[0]);  // va en un print y no puede ir en exit failure por el args[0]
		free_char_array(args, i);
		exit_program(NULL, 0, 0, "");
	}
	path = ft_strjoin(directory, args[0]);
	return (execve(path, args, envp));
}

char	*find_directory(DIR **dir, char **args)  // DIR ** para poder pasar DIR* argumento sin inicializar (repartir variables por Norminette)
{
	char			*path_var;
	char			**paths;
	char			*path;
	int				i;
	struct dirent	*d;

	path_var = getenv("PATH");
	paths = ft_split(path_var, ':');
	i = 0;

	while (paths[i])
	{
		*dir = opendir(paths[i]);
		errno = 0;
		while (*dir && errno == 0 && (d = readdir(*dir)))
		{
			if (!ft_strcmp(d->d_name, args[0]))
			{
				path = ft_strjoin(paths[i], "/");
				free_char_array(paths, double_len(paths));
				return (path);
			}
		}
		closedir(*dir);
		i++;
	}
	free_char_array(paths, double_len(paths));
	return (NULL);
}

void	execute_instr(t_ast_node *instr, char ***envp, int *fds)
{
	t_ast_node	*curr;

	int			pipe_ends[2];

	pipe(fds);
	pipe_ends[1] = fds[WRITE];
	pipe_ends[0] = fds[READ];
	execute_cmd(instr->left, STDIN_FILENO, fds[WRITE], envp, fds);
	curr = instr->right;
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(fds[WRITE]);
		pipe(fds);
		execute_cmd(curr->left, pipe_ends[0], fds[WRITE], envp, fds);
		close(pipe_ends[0]);
		pipe_ends[0] = fds[READ];
		curr = curr->right;
	}
	close(fds[WRITE]);
	execute_cmd(curr, fds[READ], STDOUT_FILENO, envp, fds);
	close(fds[READ]);
}

void	execute_job(t_ast_node *job, char ***envp)
{
	int			fds[2];

	if (job == NULL)
		return ;
	if (job->type == PIPE_NODE)
	{
		execute_instr(job, envp, fds);
	}
	else
	{
		execute_cmd(job, STDIN_FILENO, STDOUT_FILENO, envp, fds);
	}
	while (waitpid(-1, NULL, 0) > 0){ }
}

void	execute_seq(t_ast_node *seq, char ***envp)
{
	if (seq == NULL)
		return ;
	if (seq->type == SEQ_NODE)
	{
		execute_job(seq->left, envp);
		execute_seq(seq->right, envp);
	}
	else
		execute_job(seq, envp);
}

void	ft_execute(t_ast_node *syntax_tree, char ***envp)
{
	execute_seq(syntax_tree, envp);
}
