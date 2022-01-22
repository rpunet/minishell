/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:23:16 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/22 21:44:25 by jcarrete         ###   ########.fr       */
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
	return (create_parent_node(SEQ_NODE, NULL, job, NULL));
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
	return (create_parent_node(SEQ_NODE, NULL, job, seq));
}
