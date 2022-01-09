/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:54:18 by rpunet            #+#    #+#             */
/*   Updated: 2022/01/09 20:31:24 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_instr_pipe(t_minishell *shell, t_exec *exec, char ***envp)
{
	t_ast_node	*curr;

	pipe(exec->fds);
	shell->std.out = exec->fds[WRITE];
	curr = exec->cmd_node->right;
	exec->cmd_node = exec->cmd_node->left;
	execute_instr(shell, exec, envp);
	shell->std.in = exec->fds[READ];
	while (curr != NULL && curr->type == PIPE_NODE)
	{
		close(exec->fds[WRITE]);
		pipe(exec->fds);
		shell->std.out = exec->fds[WRITE];
		exec->cmd_node = curr->left;
		execute_instr(shell, exec, envp);
		close(shell->std.in);
		shell->std.in = exec->fds[READ];
		curr = curr->right;
	}
	close(exec->fds[WRITE]);
	shell->std.out = STDOUT_FILENO;
	exec->cmd_node = curr;
	execute_instr(shell, exec, envp);
	close(exec->fds[READ]);
}

void	execute_instr(t_minishell *shell, t_exec *exec, char ***envp)
{
	if (exec->cmd_node->type == REDIR_NODE)
	{
		shell->std.out = open(exec->cmd_node->data, \
								O_CREAT | O_WRONLY | O_TRUNC, S_IRWUGO);
		exec->cmd_node = exec->cmd_node->left;
		execute_cmd(shell, exec, envp);
	}
	else if (exec->cmd_node->type == APPEND_NODE)
	{
		shell->std.out = open(exec->cmd_node->data, \
								O_CREAT | O_WRONLY | O_APPEND, S_IRWUGO);
		exec->cmd_node = exec->cmd_node->left;
		execute_cmd(shell, exec, envp);
	}
	else
		execute_cmd(shell, exec, envp);
}

void	execute_job(t_minishell *shell, t_ast_node *job, char ***envp)
{
	t_exec		exec;

	if (job == NULL)
		return ;
	shell->std.in = STDIN_FILENO;
	shell->std.out = STDOUT_FILENO;
	exec.cmd_node = job;
	if (job->type == PIPE_NODE)
	{
		execute_instr_pipe(shell, &exec, envp);
	}
	else
		execute_instr(shell, &exec, envp);
	while (waitpid(-1, NULL, 0) > 0)
	{
		do_nothing(NULL);
	}
}

void	execute_seq(t_minishell *shell, t_ast_node *seq, char ***envp)
{
	if (seq == NULL)
		return ;
	if (seq->type == SEQ_NODE)
	{
		execute_job(shell, seq->left, envp);
		execute_seq(shell, seq->right, envp);
	}
	else
		execute_job(shell, seq, envp);
}

void	ft_execute(t_ast_node *syntax_tree, char ***envp)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	execute_seq(shell, syntax_tree, envp);
}
