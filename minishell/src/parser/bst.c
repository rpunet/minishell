/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:19:55 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/27 22:42:38 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bst	*create_bst_node(void)
{
	t_bst	*statement;

	statement = malloc(sizeof(t_bst));
	if (statement == NULL)
		return (NULL);
	statement->operator = 0;
	statement->tree = NULL;
	statement->child = NULL;
	statement->next = NULL;
	return (statement);
}

void	parse_brackets(t_minishell *shell)
{
	(void)shell;
}
