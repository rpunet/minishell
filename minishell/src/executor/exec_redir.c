/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 22:59:24 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/20 00:06:11 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_redir(t_minishell *shell, t_exec *exec)
{
	int	i;

	i = 0;
	printf("estoy en execute loop redir\n");
	while (exec->cmd_node->type == REDIR_NODE)
	{
		printf("i es %d\n", i++);
		if (exec->cmd_node->left != NULL && \
			exec->cmd_node->left->type == REDIR_NODE)
			close(shell->std.out);
		shell->std.out = open(exec->cmd_node->data, \
								O_CREAT | O_WRONLY | O_TRUNC, S_IRWUGO);
		if (exec->cmd_node->right != NULL)
			exec->cmd_node = exec->cmd_node->right;
		else
			break ;
	}
}

void	execute_redirection(t_minishell *shell, t_exec *exec, char ***envp)
{
	t_ast_node	*cmd;

	cmd = exec->cmd_node->left;
	if (exec->cmd_node->type == REDIR_NODE)
		loop_redir(shell, exec);
	else if (exec->cmd_node->type == APPEND_NODE)
		shell->std.out = open(exec->cmd_node->data, \
							O_CREAT | O_WRONLY | O_APPEND, S_IRWUGO);
	else if (exec->cmd_node->type == INDIR_NODE)
		shell->std.in = open(exec->cmd_node->data, O_RDONLY);
	else if (exec->cmd_node->type == LIMIT_NODE)
		shell->std.in = here_doc(shell, exec);
	exec->cmd_node = cmd;
	execute_cmd(shell, exec, envp);
}
