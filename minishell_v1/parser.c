/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:36:14 by rpunet            #+#    #+#             */
/*   Updated: 2021/02/28 12:06:58 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
----------shell grammar rules:---------------

SEQUENCE		:=		JOB
						JOB	;
						JOB	;	SEQUENCE

JOB				:=		INSTR
						INSTR	|	JOB

INSTR			:=		CMD
						CMD		>	filename
						CMD		<	filename
						CMD		>>	filename			¿¿cómo incluir varias >  > ?? el test lo prueba

CMD				:=		cmdpath	TOKENLIST

TOKENLIST		:=		token	TOKENLIST
						(empty)
*/

t_tok	*g_current_tok;

void		ASTdelete(t_ASTnode *node)
{
	if (node == NULL)
		return ;
	if (node->type == DATA)
		free(node->data);
	ASTdelete(node->left);
	ASTdelete(node->right);
	free(node);
}

int			terminal(int	tokentype)
{
	if (g_current_tok == NULL)
		return (0);
	if (g_current_tok->type == tokentype)
	{
		g_current_tok = g_current_tok->next;
		return (1);
	}
//	g_current_tok = g_current_tok->next;
	return (0);
}
// -----------------------------------------------------------------------------------------------
t_ASTnode	*GR_seq()
{
	t_ASTnode	*node;
	t_tok		*save;

	save = g_current_tok;
	if (node = gr_seq_1() != NULL)
		return (node);
	g_current_tok = save;
	if (node = gr_seq_2() != NULL)
		return (node);
	g_current_tok = save;
	if (node = gr_seq_3() != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_seq_1()
{
	return (GR_job());
}

t_ASTnode	*gr_seq_2()
{
	t_ASTnode	*seq;
	t_ASTnode	*job;

	if ((job = GR_job()) == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	seq = malloc(sizeof(t_ASTnode *));  // CHECK MALLOC--> AQUI O EN UNA FUNCION PARA DAR LOS VALORES AL NODO
	seq->type = SEQ;
	seq->left = job;
	seq->right = NULL;
	return (seq);
}

t_ASTnode	*gr_seq_3()
{
	t_ASTnode	*seq;
	t_ASTnode	*seq_sub;
	t_ASTnode	*job;

	if ((job = GR_job()) == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	if ((seq_sub == GR_seq()) == NULL)
	{
		ASTdelete(job);
		return (NULL);
	}
	seq = malloc(sizeof(t_ASTnode *));
	seq->type = SEQ;
	seq->left = job;
	seq->right = seq_sub;
	return (seq);
}
// ----------------------------------------------------------------------------------------------

t_ASTnode	*GR_job()
{
	t_ASTnode	*node;
	t_tok		*save;

	save = g_current_tok;
	if ((node = gr_job_1()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_job_2()) != NULL)
		return (node);
	return (NULL);
}




int		parser(t_lex *lexer, t_ASTnode **syntax_tree)
{
	// error check
	g_current_tok = lexer->list_token;
	*syntax_tree = gr_sequence();
	//check errors

	return (0);
}
