/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:15:46 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/03 17:21:33 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*tok_init(int datasize)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (token == NULL)
		return (NULL);
	token->data = malloc(datasize + 1);
	if (token->data == NULL)
		return (NULL);
	token->type = T_NULTOK;
	token->next = NULL;
	return (token);
}

void	tok_delete(t_tok **token)
{
	t_tok	*next;

	if ((*token) != NULL)
	{
		(*token)->data = ft_memfree((*token)->data, NULL);
		next = (*token)->next;
		(*token) = ft_memfree((*token), NULL);
		tok_delete(&next);
	}
}
