/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:42:52 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/10 23:18:34 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_fds(t_ft_builtins ptr, t_pipe *fd_pipe, \
						char ***envp, char **args)
{
	int	save;

	save = dup(STDOUT_FILENO);
	if (fd_pipe->out == 1)
		ptr(args, envp);
	else
	{
		dup2(fd_pipe->out, STDOUT_FILENO);
		close(fd_pipe->out);
		ptr(args, envp);
		dup2(save, STDOUT_FILENO);
		close(save);
	}
}

static void	child_process(t_exec *exec, char ***envp, int i)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	if (shell->std.in != 0)
	{
		dup2(shell->std.in, STDIN_FILENO);
		close(shell->std.in);
	}
	if (shell->std.out != 1)
	{
		close(exec->fds[READ]);
		dup2(shell->std.out, STDOUT_FILENO);
		close(shell->std.out);
	}
	if (exec_process(exec->args, *envp, i) == -1)
	{
		free_char_array(exec->args, i);
		exit_program(NULL, 0, 0, "Error de execve");
	}
}

static void	create_child(t_exec *exec, char ***envp, int i)
{
	pid_t		pid;
	int			status;
	t_minishell	*shell;

	shell = get_minishell(NULL);
	pid = fork();
	if (pid == 0)
		child_process(exec, envp, i);
	else if (pid < 0)
	{
		free_char_array(exec->args, i);
		exit_program(NULL, 0, E_EXECUTE, "CMD PID < 0");
	}
	if (waitpid(pid, &status, 0) == -1)
		exit_program(NULL, 0, E_EXECUTE, "");
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = EXIT_STATUS + WTERMSIG(status);
	else
		shell->exit_code = EB_CATCHALL;
}

static int	count_curr(t_exec *exec)
{
	int			i;
	t_ast_node	*curr;

	i = count_commands(exec->cmd_node);
	exec->args = malloc(sizeof(char *) * (i + 1));
	if (exec->args == NULL)
		exit_program(NULL, 0, 0, "CMD Malloc is NULL");
	curr = exec->cmd_node;
	i = 0;
	while (curr != NULL && \
		(curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
	{
		exec->args[i] = ft_strdup(curr->data);
		curr = curr->right;
		i++;
	}
	exec->args[i] = NULL;
	return (i);
}

void	execute_cmd(t_minishell *shell, t_exec *exec, char ***envp)
{
	int			i;

	i = count_curr(exec);
	if ((exec->cmd_node != NULL || exec->cmd_node->type == CMDNAME_NODE) \
		&& i > 0)
	{
		if (!ft_strcmp(exec->args[0], "pwd"))
			manage_fds(&ft_pwd, &shell->std, envp, exec->args);
		else if (!ft_strcmp(exec->args[0], "echo"))
			manage_fds(&ft_echo, &shell->std, envp, exec->args);
		else if (!ft_strcmp(exec->args[0], "exit"))
			ft_exit(exec->args);
		else if (!ft_strcmp(exec->args[0], "cd") && shell->std.in == \
			STDIN_FILENO && shell->std.out == STDOUT_FILENO)
			ft_cd(exec->args, envp);
		else if (!ft_strcmp(exec->args[0], "export"))
			manage_fds(&ft_export, &shell->std, envp, exec->args);
		else if (!ft_strcmp(exec->args[0], "unset"))
			ft_unset(&exec->args[1], envp);
		else
			create_child(exec, envp, i);
	}
	free_char_array(exec->args, i);
}
