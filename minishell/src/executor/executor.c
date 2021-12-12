/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/12 00:34:06 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_instr(t_ast_node *instr, char ***envp, int *fds)
{
	t_ast_node	*curr;
	t_pipe		fd_pipe;

	pipe(fds);
	fd_pipe.in = STDIN_FILENO;
	fd_pipe.out = fds[WRITE];
	execute_cmd(instr->left, fd_pipe, envp, fds);
	fd_pipe.in = fds[READ];
	curr = instr->right;
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(fds[WRITE]);
		pipe(fds);
		fd_pipe.out = fds[WRITE];
		execute_cmd(curr->left, fd_pipe, envp, fds);
		close(fd_pipe.in);
		fd_pipe.in = fds[READ];
		curr = curr->right;
	}
	close(fds[WRITE]);
	fd_pipe.out = STDOUT_FILENO;
	execute_cmd(curr, fd_pipe, envp, fds);
	close(fds[READ]);
}

void	execute_job(t_ast_node *job, char ***envp)
{
	int	fds[2];

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
