/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:30:08 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/09 21:30:14 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*set_parent(t_ast_node	**parent, int type)
{
	t_ast_node	*cmd;
	char		*filename;

	filename = NULL;
	cmd = gr_cmd();
	if (cmd == NULL)
	{
		*parent = ft_memfree(*parent, NULL);
		return (NULL);
	}
	if (terminal(type))
	{
		*parent = ft_memfree(*parent, NULL);
		ast_delete(&cmd);
		return (NULL);
	}
	if (g_current_tok->data != NULL)
		filename = ft_strdup(g_current_tok->data);
	if (terminal(T_TOKEN))
	{
		ast_delete(&cmd);
		return (return_null(filename));
	}
	(*parent)->data = filename;
	(*parent)->left = cmd;
	return (*parent);
}

t_ast_node	*gr_instr(void)
{
	t_tok		*save;
	t_ast_node	*node;

	save = g_current_tok;
	node = gr_instr_4();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_instr_3();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_instr_2();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_instr_1();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_instr_1(void)
{
	return (gr_cmd());
}

t_ast_node	*gr_instr_2(void)
{
	t_ast_node	*parent;

	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = REDIR_NODE;
	parent->right = NULL;
	return (set_parent(&parent, T_REDIR));
}

t_ast_node	*gr_instr_3(void)
{
	t_ast_node	*parent;

	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = INDIR_NODE;
	parent->right = NULL;
	return (set_parent(&parent, T_INDIR));
}

t_ast_node	*gr_instr_4(void)
{
	t_ast_node	*parent;

	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = APPEND_NODE;
	parent->right = NULL;
	return (set_parent(&parent, T_APPEND));
}
