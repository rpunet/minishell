/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2022/01/09 13:11:49 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_instr_pipe(t_exec *exec, char ***envp)
{
	t_ast_node	*curr;

	pipe(exec->fds);
	exec->fd_pipe.out = exec->fds[WRITE];
	curr = exec->cmd_node->right;
	exec->cmd_node = exec->cmd_node->left;
	execute_instr(exec, envp);
	exec->fd_pipe.in = exec->fds[READ];
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(exec->fds[WRITE]);
		pipe(exec->fds);
		exec->fd_pipe.out = exec->fds[WRITE];
		exec->cmd_node = curr->left;
		execute_instr(exec, envp);
		close(exec->fd_pipe.in);
		exec->fd_pipe.in = exec->fds[READ];
		curr = curr->right;
	}
	close(exec->fds[WRITE]);
	exec->fd_pipe.out = STDOUT_FILENO;
	exec->cmd_node = curr;
	execute_instr(exec, envp);
	close(exec->fds[READ]);
}

void	execute_instr(t_exec *exec, char ***envp)
{
	ft_printf("Type is %d\n", exec->cmd_node->type);
	if (exec->cmd_node->type == T_REDIR)
	{
		ft_printf("He llegado bien\n");
		ft_printf("Data es %s\n", exec->cmd_node->right->data);
		exec->fd_pipe.out = open(exec->cmd_node->right->data, \
								O_CREAT | O_WRONLY | O_TRUNC, S_IRWUGO);
		ft_printf("fd es %d\n", exec->fd_pipe.out);
		execute_cmd(exec, envp);
		close(exec->fd_pipe.out);
	}
	else
		execute_cmd(exec, envp);
}

void	execute_job(t_ast_node *job, char ***envp)
{
	t_exec	exec;

	if (job == NULL)
		return ;
	exec.fd_pipe.in = STDIN_FILENO;
	exec.fd_pipe.out = STDOUT_FILENO;
	exec.cmd_node = job;
	if (job->type == PIPE_NODE)
	{
		execute_instr_pipe(&exec, envp);
	}
	else
		execute_instr(&exec, envp);
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
