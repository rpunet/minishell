/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2021/04/04 11:06:38 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_CMD(t_ASTnode *cmd_node, int in, int out)
{
	int			i;
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
			exit_failure();
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
		if (i > 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (in != 0)
					dup2(in, STDIN_FILENO);
				if (out != 1)
					dup2(out, STDOUT_FILENO);
				if (execvp(args[0], args) == -1)
					exit_failure("Error de exec");
			}
			else if (pid < 0)
				exit_failure();
			while (waitpid(pid, NULL, 0) <= 0)
				do_nothing();
		}
	}
}

void	execute_INSTR(t_ASTnode *instr)
{
	t_ASTnode	*curr;
	int			fds[2];
	int			pipe_ends[2];

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
		close(pipe_ends[0]);
		pipe_ends[0] = fds[READ];
		curr = curr->right;
	}
	close(fds[WRITE]);
	execute_CMD(curr, fds[READ], STDOUT_FILENO);
	close(fds[READ]);
}

void	execute_JOB(t_ASTnode *job)
{
	if (job == NULL)
		return ;
	if (job->type == PIPE_NODE)
	{
		execute_INSTR(job);
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

void	ft_execute(t_ASTnode *syntax_tree)
{
	execute_SEQ(syntax_tree);
}
