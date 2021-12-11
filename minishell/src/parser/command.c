/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:27:42 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/07 12:00:12 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*gr_cmd(void)
{
	t_ast_node	*node;

	node = gr_cmd_1();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_cmd_1(void)
{
	t_ast_node	*parent;
	t_ast_node	*tokenlist;
	char		*dataname;

	dataname = NULL;
	if (g_current_tok != NULL)
		dataname = ft_strdup(g_current_tok->data);
	if (terminal(T_TOKEN))
		return (return_null(dataname));
	tokenlist = gr_tokenlist();
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = CMDNAME_NODE;
	parent->data = dataname;
	parent->left = NULL;
	parent->right = tokenlist;
	return (parent);
}

t_ast_node	*gr_tokenlist(void)
{
	t_tok		*save;
	t_ast_node	*node;

	save = g_current_tok;
	node = gr_tokenlist_1();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_tokenlist_2();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_tokenlist_1(void)
{
	t_ast_node	*parent;
	t_ast_node	*tokenlist;
	char		*dataarg;

	dataarg = NULL;
	if (g_current_tok != NULL)
		dataarg = ft_strdup(g_current_tok->data);
	if (terminal(T_TOKEN))
		return (return_null(dataarg));
	tokenlist = gr_tokenlist();
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->data = dataarg;
	parent->type = TOKEN_NODE;
	parent->left = NULL;
	parent->right = tokenlist;
	return (parent);
}

t_ast_node	*gr_tokenlist_2(void)
{
	return (NULL);
}
