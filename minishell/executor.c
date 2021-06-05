/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/06/05 17:41:49 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_CMD(t_ASTnode *cmd_node, int in, int out, char **envp, int *fds)
{
	int			i;
	do_nothing(fds);

	char		**args;
	t_ASTnode	*curr;
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
			exit_failure("CMD Malloc is NULL");
		curr = cmd_node;
		i = 0;
		while (curr != NULL && \
			(curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
		{
			args[i] = ft_strdup(curr->data);
			curr = curr->right;
			i++;
		}
		args[i] = NULL;
		if (i > 0)			//	if (!check_builtin())  ...
		{
			if (!ft_strcmp(args[0], "exit"))			//	EXIT TMB TIENE QUE IR EN PARENT
			{
				ft_exit();
			}
			else if (!ft_strcmp(args[0], "cd"))			// EN PÀRENT... ALGUNO MAŚ?
			{
				if (in == STDIN_FILENO && out == STDOUT_FILENO)
					ft_cd(args, envp);
			}
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
					if (check_builtins(args, envp))
					{
						free_char_array(args, i);
						ft_putstr_fd("vemos esto aqui\n", 1);
						exit(0);
					}
					if (exec_process(args, envp, i) == -1)
					{
						free_char_array(args, i);
						exit_failure("Error de execve");   // salir sin mensaje, o devolver distintos errores para distinos mensajes
					}
				}
				else if (pid < 0)
				{
					free_char_array(args, i);
					exit_failure("CMD PID < 0");
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
		ft_printf("%s: Command not found\n", args[0]);  // va en un print y no puede ir en exit failure por el args[0]
		free_char_array(args, i);
		exit_failure("");
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
			if (!ft_strncmp(d->d_name, args[0], ft_strlen(args[0]) + 1))
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

void	execute_INSTR(t_ASTnode *instr, char **envp, int *fds)
{
	t_ASTnode	*curr;

	int			pipe_ends[2];

	pipe(fds);
	pipe_ends[1] = fds[WRITE];
	pipe_ends[0] = fds[READ];
	execute_CMD(instr->left, STDIN_FILENO, fds[WRITE], envp, fds);
	curr = instr->right;
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(fds[WRITE]);
		pipe(fds);
		execute_CMD(curr->left, pipe_ends[0], fds[WRITE], envp, fds);
		close(pipe_ends[0]);
		pipe_ends[0] = fds[READ];
		curr = curr->right;
	}
	close(fds[WRITE]);
	execute_CMD(curr, fds[READ], STDOUT_FILENO, envp, fds);
	close(fds[READ]);
}

void	execute_JOB(t_ASTnode *job, char **envp)
{
	int			fds[2];

	if (job == NULL)
		return ;
	if (job->type == PIPE_NODE)
	{
		execute_INSTR(job, envp, fds);
	}
	else
	{
		execute_CMD(job, STDIN_FILENO, STDOUT_FILENO, envp, fds);
	}
	while (waitpid(-1, NULL, 0) > 0) {}
}

void	execute_SEQ(t_ASTnode *seq, char **envp)
{
	if (seq == NULL)
		return ;
	if (seq->type == SEQ_NODE)
	{
		execute_JOB(seq->left, envp);
		execute_SEQ(seq->right, envp);
	}
	else
		execute_JOB(seq, envp);
}

void	ft_execute(t_ASTnode *syntax_tree, char **envp)
{
	execute_SEQ(syntax_tree, envp);


}
