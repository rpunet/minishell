/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:04:33 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/22 21:41:43 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_parent_node(int type, char *data, \
				t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*ret;

	ret = malloc(sizeof(t_ast_node));
	if (ret == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	ret->type = type;
	ret->data = data;
	ret->left = left;
	ret->right = right;
	return (ret);
}
