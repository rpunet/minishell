/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:26:05 by rpunet            #+#    #+#             */
/*   Updated: 2022/01/22 19:37:29 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*gr_dir(void)
{
	t_tok		*save;
	t_ast_node	*node;

	save = g_current_tok;
	node = gr_dir_2();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_dir_1();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_dir_2(void)
{
	t_ast_node	*parent;
	t_ast_node	*filename;
	t_ast_node	*dir;
	int			dir_type;

	filename = gr_dir_1();
	if (filename == NULL)
		return (NULL);
	if (g_current_tok != NULL)
		dir_type = get_dir_type();
	if (terminal_redir())
	{
		ast_delete(&filename);
		return (NULL);
	}
	dir = gr_dir();
	if (dir == NULL)
	{
		ast_delete(&filename);
		return (NULL);
	}
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = dir_type;
	parent->left = filename;
	parent->right = dir;
	return (parent);
}

t_ast_node	*gr_dir_1(void)
{
	t_ast_node	*parent;
	char		*dataname;

	dataname = NULL;
	if (g_current_tok != NULL)
		dataname = ft_strdup(g_current_tok->data);
	if (terminal(T_TOKEN))
		return (return_null(dataname));
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = FILENAME_NODE;
	parent->data = dataname;
	parent->left = NULL;
	parent->right = NULL;
	return (parent);
}
