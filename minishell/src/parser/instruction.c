/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:30:08 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/22 19:37:16 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*gr_instr(void)
{
	t_tok		*save;
	t_ast_node	*node;

	save = g_current_tok;
	node = gr_instr_2();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_instr_1();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_instr_2(void)
{
	t_ast_node	*cmd;
	t_ast_node	*dir;
	t_ast_node	*parent;
	int			dir_type;

	cmd = gr_cmd();
	if (cmd == NULL)
		return (NULL);
	if (g_current_tok != NULL)
		dir_type = get_dir_type();
	if (terminal_redir())
	{
		ast_delete(&cmd);
		return (NULL);
	}
	dir = gr_dir();
	if (dir == NULL)
	{
		ast_delete(&cmd);
		return (NULL);
	}
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = dir_type;
	parent->data = NULL;
	parent->left = cmd;
	parent->right = dir;
	return (parent);
}

t_ast_node	*gr_instr_1(void)
{
	return (gr_cmd());
}

int			get_dir_type()
{
	if (g_current_tok->type == T_REDIR)
		return (REDIR_NODE);
	else if (g_current_tok->type == T_INDIR)
		return (INDIR_NODE);
	else if (g_current_tok->type == T_APPEND)
		return (APPEND_NODE);
	else if (g_current_tok->type == T_LIMITER)
		return (LIMIT_NODE);
	return (0);
}
