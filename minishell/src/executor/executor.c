/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/13 20:37:59 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_instr(t_exec *exec, char ***envp)
{
	t_ast_node	*curr;

	pipe(exec->fds);
	exec->fd_pipe.in = STDIN_FILENO;
	exec->fd_pipe.out = exec->fds[WRITE];
	curr = exec->cmd_node->right;
	exec->cmd_node = exec->cmd_node->left;
	execute_cmd(exec, envp);
	exec->fd_pipe.in = exec->fds[READ];
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(exec->fds[WRITE]);
		pipe(exec->fds);
		exec->fd_pipe.out = exec->fds[WRITE];
		exec->cmd_node = curr->left;
		execute_cmd(exec, envp);
		close(exec->fd_pipe.in);
		exec->fd_pipe.in = exec->fds[READ];
		curr = curr->right;
	}
	close(exec->fds[WRITE]);
	exec->fd_pipe.out = STDOUT_FILENO;
	exec->cmd_node = curr;
	execute_cmd(exec, envp);
	close(exec->fds[READ]);
}

void	execute_job(t_ast_node *job, char ***envp)
{
	t_exec	exec;

	if (job == NULL)
		return ;
	exec.cmd_node = job;
	if (job->type == PIPE_NODE)
	{
		execute_instr(&exec, envp);
	}
	else
	{
		exec.fd_pipe.in = STDIN_FILENO;
		exec.fd_pipe.out = STDOUT_FILENO;
		execute_cmd(&exec, envp);
	}
	while (waitpid(-1, NULL, 0) > 0)
	{
		do_nothing(NULL);
	}
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
