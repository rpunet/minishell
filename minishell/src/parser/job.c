/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:29:33 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/03 17:19:16 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*gr_job(void)
{
	t_ast_node	*node;
	t_tok		*save;

	save = g_current_tok;
	node = gr_job_2();
	if (node != NULL)
		return (node);
	g_current_tok = save;
	node = gr_job_1();
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast_node	*gr_job_1(void)
{
	return (gr_instr());
}

t_ast_node	*gr_job_2(void)
{
	t_ast_node	*parent;
	t_ast_node	*job;
	t_ast_node	*instr;

	instr = gr_instr();
	if (instr == NULL)
		return (NULL);
	if (terminal(T_PIPE))
	{
		ast_delete(&instr);
		return (NULL);
	}
	job = gr_job();
	if (job == NULL)
	{
		ast_delete(&instr);
		return (NULL);
	}
	parent = malloc(sizeof(t_ast_node));
	if (parent == NULL)
		exit_program(NULL, 0, E_MEM, strerror(errno));
	parent->type = PIPE_NODE;
	parent->left = instr;
	parent->right = job;
	return (parent);
}
