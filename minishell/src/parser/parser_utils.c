/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 21:04:33 by jcarrete          #+#    #+#             */
/*   Updated: 2022/02/04 01:02:40 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_delete(t_ast_node **node)
{
	t_ast_node	*right;
	t_ast_node	*left;

	if ((*node) == NULL)
		return ;
	if ((*node)->data != NULL)
		(*node)->data = ft_memfree((*node)->data, NULL);
	right = (*node)->right;
	left = (*node)->left;
	(*node) = ft_memfree((*node), NULL);
	ast_delete(&left);
	ast_delete(&right);
}

void	delete_single_ast(t_ast_node **node)
{
	if ((*node) == NULL)
		return ;
	if ((*node)->type >= CMDNAME_NODE && (*node)->data != NULL)
		(*node)->data = ft_memfree((*node)->data, NULL);
	if ((*node)->right != NULL)
		(*node)->right->left = NULL;
	if ((*node)->left != NULL)
		(*node)->left->right = NULL;
	(*node) = ft_memfree((*node), NULL);
}

t_ast_node	*create_parent_node(int type, char *data, \
				t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*ret;

	ret = malloc(sizeof(t_ast_node));
	if (ret == NULL)
		exit_program(NULL, F_SHELL, E_MEM, strerror(errno));
	ret->type = type;
	ret->data = data;
	ret->left = left;
	ret->right = right;
	return (ret);
}
