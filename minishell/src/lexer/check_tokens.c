/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:09:34 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/27 00:12:22 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_parenthesis(t_tok *curr, t_tok *prev, int *bracket, int cond)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	if (curr->type == T_BRAKET_OPEN)
	{
		(*bracket)++;
		(shell->lexer.brackets)++;
	}
	if (curr->type == T_BRAKET_CLOSE)
	{
		(*bracket)--;
		if (*bracket < 0 || prev->type == T_BRAKET_OPEN)
			return (FALSE);
	}
	if (curr->next == NULL && *bracket > 0)
		return (FALSE);
	return (cond);
}

void	check_tokens(t_minishell *shell, t_tok *list)
{
	int		braket;
	int		condition;
	t_tok	*curr;
	t_tok	*prev;

	braket = 0;
	shell->lexer.brackets = 0;
	curr = list;
	prev = NULL;
	while (curr)
	{
		condition = TRUE;
		if (check_if_redir(curr->type) && curr->next->type > 0)
			condition = FALSE;
		if ((curr->type == T_AND || curr->type == T_OR || \
			curr->type == T_PIPE) && (prev == NULL || curr->next == NULL || \
			(prev->type >= 0 && prev->type != T_BRAKET_CLOSE)))
			condition = FALSE;
		condition = check_parenthesis(curr, prev, &braket, condition);
		if (condition == FALSE)
			exit_program(shell, F_SHELL, E_SYNTAX, curr->data);
		prev = curr;
		curr = curr->next;
	}
}
