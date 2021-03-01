/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/03/01 20:59:26 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute_CMD()
{
	//if (   REDIR; INDIR)
	//...				aquií irán las redireecciones un poco más adelante que bastante liado esta esto ya

	if (    type = CMDPATH_NODE)
		e
}

void	execute_INSTR(t_ASTnode *instr)
{
	t_ASTnode	*curr;
	int			fds[2];
	int			pipe_ends[2];
	t_cmd		cmd;

	pipe(fds);
	pipe_ends[1] = fds[WRITE];
	pipe_ends[0] = fds[READ];
	execute_CMD(instr->left, STDIN_FILENO, fds[WRITE]);
	curr = instr->right;
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(fds[WRITE]);
		pipe(fds);
		execute_CMD(curr->left, pipe_ends[0], fds[WRITE]);
		close(pipe_ends[0])
		pipe_ends[0] = fds[READ];
		curr = curr->right;
	}
	close(fds[WRITE]);
	execute_CMD(curr, fds[READ], STDOUT_FILENO);
	close(fds[READ]);
}

void	execute_JOB(t_ASTnode *job)
{
	t_cmd	cmd;

	if (job == NULL)
		return ;
	if (job->type == PIPE_NODE)
	{
		execute_INSTR(job->left);
	//	execute_JOB(job->right);
	}
	else
	{
		execute_CMD(job, STDIN_FILENO, STDOUT_FILENO);
	}
}

void	execute_SEQ(t_ASTnode *seq)
{
	if (seq == NULL)
		return ;
	if (seq->type == SEQ_NODE)
	{
		execute_JOB(seq->left);
		execute_SEQ(seq->right);
	}
	else
		execute_JOB(seq);
}

void	execute(t_ASTnode *syntax_tree)
{
	execute_SEQ(syntax_tree);
}
