/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:27:46 by rpunet            #+#    #+#             */
/*   Updated: 2021/04/04 11:07:52 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexer(char *line, t_lex *lexer, int size)
{
	t_tok	*token;
	int		c;
	int		i;
	int		j;
	int		state;

	token = tok_init(size);
	lexer->list_token = token;
	state = GENERAL;
	i = 0;
	j = 0;
	while (line[i] != 0)
	{
		c = (line[i]);
		if (state == GENERAL)
		{
			if (c == '\'')
			{
				state = QUOTED;
				token->type = TOKEN;
			}
			else if (c == '\"')
			{
				state = DQUOTED;
				token->type = TOKEN;
			}
			else if (c == '\\')
			{
				token->data[j] = line[++i];
				j++;
				token->type = TOKEN;
			}
			else if (c == ' ')
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = tok_init(size - i);
					token = token->next;
					j = 0;
				}
			}
			else if (c == ';' || c == '>' || c == '<' || c == 66 || c == '|')
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = tok_init(1);
					token = token->next;
					j = 0;
				}
				token->data[0] = (char)c;
				token->data[1] = 0;
				token->type = c;
				token->next = tok_init(size - i);
				token = token->next;
			}
			else
			{
				token->data[j] = (char)c;
				j++;
				token->type = TOKEN;
			}
		}
		else if (state == QUOTED)
		{
			if (c == '\'')
				state = GENERAL;
			else
				token->data[j++] = (char)c;
		}
		else if (state == DQUOTED)
		{
			if (c == '\"')
				state = GENERAL;
			else
				token->data[j++] = (char)c;
		}
		i++;
	}
	token->data[j] = 0;
	return (0);
}
