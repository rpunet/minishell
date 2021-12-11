/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:36:14 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/11 18:21:18 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ----------shell grammar rules:---------------
** SEQUENCE			:=		JOB		;	SEQUENCE
** 							JOB		;
** 							JOB
**
** JOB				:=		INSTR
** 							INSTR	|	JOB
**
** INSTR			:=		CMD
** 							CMD		>	filename
** 							CMD		<	filename
** 							CMD		>>	filename
**
** CMD				:=		cmdname	TOKENLIST
**
** TOKENLIST		:=		token	TOKENLIST
** 							(empty)
*/

void	ast_delete(t_ast_node *node)
{
	if (node == NULL)
		return ;
	if (node->type >= REDIR_NODE)
		node->data = ft_memfree(node->data, NULL);
	ast_delete(node->left);
	ast_delete(node->right);
	node = ft_memfree(node, NULL);
}

int	terminal(int tokentype)
{
	if (g_current_tok == NULL)
		return (EXIT_FAILURE);
	if (g_current_tok->type == tokentype)
	{
		g_current_tok = g_current_tok->next;
		return (EXIT_SUCCESS);
	}
	g_current_tok = g_current_tok->next;
	return (EXIT_FAILURE);
}

/*
** ----------------------  TREE ROOT ----------------------------
*/

int	ft_parser(t_lex *lexer, t_ast_node **syntax_tree)
{
	g_current_tok = lexer->list_token;
	*syntax_tree = gr_seq();
	if (g_current_tok != NULL && g_current_tok->type != T_NULTOK)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
