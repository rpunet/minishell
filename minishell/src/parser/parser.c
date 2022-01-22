/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:36:14 by rpunet            #+#    #+#             */
/*   Updated: 2022/01/22 19:35:42 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ----------shell grammar rules:---------------
** SEQUENCE			:=		JOB		;	SEQUENCE
** 							JOB		;
** 							JOB
**
** JOB				:=		INSTR	|	JOB
** 							INSTR
**

** INSTR			:=		CMD		   >  DIR
							CMD

	DIR				:=		filename   >  DIR
	 						filename


** 							CMD		>	filename
** 							CMD		<	filename
** 							CMD		>>	filename
** 							CMD		<<	limiter
**
** CMD				:=		cmdname	TOKENLIST
**
** TOKENLIST		:=		token	TOKENLIST
** 							(empty)
*/

void	ast_delete(t_ast_node **node)
{
	t_ast_node	*right;
	t_ast_node	*left;

	if ((*node) == NULL)
		return ;
	if ((*node)->type >= CMDNAME_NODE && (*node)->data != NULL)
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

int	terminal_redir(void)
{
	if (g_current_tok == NULL)
		return (EXIT_FAILURE);
	if (g_current_tok->type == T_REDIR || g_current_tok->type == T_INDIR || g_current_tok->type == T_APPEND || g_current_tok->type == T_LIMITER)
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
	t_minishell	*shell;

	shell = get_minishell(NULL);
	g_current_tok = lexer->list_token;
	if (shell->state == ST_OK)
		*syntax_tree = gr_seq();
	if (g_current_tok != NULL && g_current_tok->type != T_NULTOK)
	{
		shell->state = ST_ERROR;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
