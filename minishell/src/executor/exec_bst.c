/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:43:33 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/27 22:36:28 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_operators(t_minishell *shell, t_bst *pre, \
							t_bst *cur, char ***envp)
{
	if (pre->operator == SEQ_NODE)
		execute_bst(shell, cur, envp);
	else if (pre->operator == AND_NODE && shell->exit_code == 0)
		execute_bst(shell, cur, envp);
	else if (pre->operator == OR_NODE && shell->exit_code != 0)
		execute_bst(shell, cur, envp);
}

void	execute_bst(t_minishell *shell, t_bst *bst, char ***envp)
{
	if (bst == NULL)
		return ;
	execute_seq(shell, shell->bst->tree, envp);
	if (bst->child)
		check_operators(shell, bst, bst->child, envp);
	if (bst->next)
		check_operators(shell, bst, bst->next, envp);
}
