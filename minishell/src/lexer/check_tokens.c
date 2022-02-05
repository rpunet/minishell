/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:09:34 by jcarrete          #+#    #+#             */
/*   Updated: 2022/02/05 15:00:45 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_parenthesis(t_tok *curr, t_tok *prev, int cond)
{
	t_minishell	*shell;
	int			bracket;

	shell = get_minishell(NULL);
	bracket = 0;
	shell->lexer.brackets = 0;
	if (curr->type == T_BRAKET_OPEN)
	{
		bracket++;
		(shell->lexer.brackets)++;
	}
	if (curr->type == T_BRAKET_CLOSE)
	{
		bracket--;
		if (bracket < 0 || prev->type == T_BRAKET_OPEN)
			return (FALSE);
	}
	if ((curr->next == NULL || curr->next->type == T_NULTOK) && bracket > 0)
		return (FALSE);
	return (cond);
}

void	check_tokens(t_minishell *shell, t_tok *list)
{
	int		condition;
	t_tok	*curr;
	t_tok	*prev;

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
		condition = check_parenthesis(curr, prev, condition);
		if (condition == FALSE)
		{
			shell->exit_code = EB_MISUSE_BUILTINS;
			print_error(shell, E_SYNTAX, curr->data);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
