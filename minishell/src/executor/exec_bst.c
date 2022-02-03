/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:43:33 by jcarrete          #+#    #+#             */
/*   Updated: 2022/02/03 18:32:43 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_operators(int next, t_bst *pre, \
							t_bst *cur, char ***envp)
{
	int			op;
	t_minishell	*shell;

	shell = get_minishell(NULL);
	op = pre->operator_child;
	if (next)
		op = pre->operator_next;
	if (op == SEQ_NODE)
		execute_bst(shell, cur, envp);
	else if (op == AND_NODE && shell->exit_code == 0)
		execute_bst(shell, cur, envp);
	else if (op == OR_NODE && shell->exit_code != 0)
		execute_bst(shell, cur, envp);
}

void	execute_bst(t_minishell *shell, t_bst *bst, char ***envp)
{
	if (bst == NULL)
		return ;
	execute_seq(shell, shell->bst->tree, envp);
	if (bst->child)
		check_operators(FALSE, bst, bst->child, envp);
	if (bst->next)
		check_operators(TRUE, bst, bst->next, envp);
}
