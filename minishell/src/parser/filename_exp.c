/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:05:45 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/31 00:46:57 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tok	*insert_wildcard(t_tok **list, t_tok *prev, t_tok *curr)
{
	(void)list;
	(void)prev;
	(void)curr;
}

static int	check_if_wildcard(char *str)
{
	int		i;
	char	quote;
	char	*str;

	i = 0;
	while (str[i])
	{
		if (str[i] == T_DQUOTE || str[i] == T_QUOTE)
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				i++;
		}
		if (str[i] == WILDCARD)
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

void	expand_filenames(t_tok **list)
{
	t_tok	*curr;
	t_tok	*prev;

	prev = NULL;
	curr = *list;
	while (curr)
	{
		if (curr->type == T_TOKEN)
		{
			if (check_if_wildcard(curr->data))
				curr = insert_wildcard(list, prev, curr);
		}
		prev = curr;
		curr = curr->next;
	}
}
