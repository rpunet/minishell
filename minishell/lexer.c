/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:27:46 by rpunet            #+#    #+#             */
/*   Updated: 2021/06/06 14:14:57 by rpunet           ###   ########.fr       */
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
	int		last_quoted = 0;

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
					if (!last_quoted)
						expand_vars(&token->data);
					token->next = tok_init(size - i);
					token = token->next;
					last_quoted = 0;
					j = 0;
				}
			}
			else if (c == ';' || c == '>' || c == '<' || c == 66 || c == '|')	//	 (el 66 seria el >> que hay que detallar)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					if (!last_quoted)
						expand_vars(&token->data);
					token->next = tok_init(1);
					token = token->next;
					last_quoted = 0;
					j = 0;
				}
				token->data[0] = (char)c;
				token->data[1] = 0;
				token->type = c;
				token->next = tok_init(size - i);
				token = token->next;
			}
			// else if (c == '$')
			// {
			// 	if (j > 0)
			// 	state = VAR;
			// 	token->type = TOKEN;
			// 	token->data
			// }
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
			{
				last_quoted = 1;
				state = GENERAL;
			}
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
		// else if (state == VAR)
		// {
		// 	if (c == ' ')
		// 		state = GENERAL;
		// 	else
		// 		token->data[j++] = (char)c;
		// }
		i++;
	}
	token->data[j] = 0;
	if (!last_quoted)
		expand_vars(&token->data);
	return (0);
}
