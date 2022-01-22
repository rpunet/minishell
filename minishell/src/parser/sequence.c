/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:23:16 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/22 19:07:13 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*gr_seq(void)
{
	t_ast_node	*node;
	t_tok		*save;

	save = g_current_tok;
	node = gr_seq_3();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_seq_2();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_seq_1();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_seq_1(void)
{
	return (gr_job());
}

t_ast_node	*gr_seq_2(void)
{
	t_ast_node	*parent;
	t_ast_node	*job;

	job = gr_job();
	if (job == NULL)
		return (NULL);
	if (terminal(T_SEMICOLON))
	{
		ast_delete(&job);
		return (NULL);
	}
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = SEQ_NODE;
	parent->data = NULL;
	parent->left = job;
	parent->right = NULL;
	return (parent);
}

t_ast_node	*gr_seq_3(void)
{
	t_ast_node	*parent;
	t_ast_node	*seq;
	t_ast_node	*job;

	job = gr_job();
	if (job == NULL)
		return (NULL);
	if (terminal(T_SEMICOLON))
	{
		ast_delete(&job);
		return (NULL);
	}
	seq = gr_seq();
	if (seq == NULL)
	{
		ast_delete(&job);
		return (NULL);
	}
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = SEQ_NODE;
	parent->data = NULL;
	parent->left = job;
	parent->right = seq;
	return (parent);
}
