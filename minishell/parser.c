/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:36:14 by rpunet            #+#    #+#             */
/*   Updated: 2021/11/25 17:07:17 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** ----------shell grammar rules:---------------
** SEQUENCE		:=		JOB		;	SEQUENCE
** 						JOB		;
** 						JOB
**
** JOB				:=		INSTR
** 						INSTR	|	JOB
**
** INSTR			:=		CMD
** 						CMD		>	filename
** 						CMD		<	filename
** 						CMD		>>	filename
**
** CMD				:=		cmdname	TOKENLIST
**
** TOKENLIST		:=		token	TOKENLIST
** 						(empty)
*/

t_tok	*g_current_tok;

void	ASTdelete(t_ASTnode *node)
{
	if (node == NULL)
		return ;
	if (node->type >= REDIR_NODE)
		node->data = ft_memfree(node->data, NULL);
	ASTdelete(node->left);
	ASTdelete(node->right);
	node = ft_memfree(node, NULL);
}

int	terminal(int tokentype)
{
	if (g_current_tok == NULL)
		return (0);
	if (g_current_tok->type == tokentype)
	{
		g_current_tok = g_current_tok->next;
		return (1);
	}
	g_current_tok = g_current_tok->next;
	return (0);
}

/*
** ----------------------  TREE ROOT ----------------------------
*/
int	ft_parser(t_lex *lexer, t_ASTnode **syntax_tree)
{
	g_current_tok = lexer->list_token;
	*syntax_tree = GR_seq();
	if (g_current_tok != NULL && g_current_tok->type != NULTOK)
		return (1);
	return (0);
}

/*
** --------------------------------------------------------------
*/
t_ASTnode	*GR_seq(void)
{
	t_ASTnode	*node;
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

t_ASTnode	*gr_seq_1(void)
{
	return (GR_job());
}

t_ASTnode	*gr_seq_2(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*job;

	job = GR_job();
	if (job == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->type = SEQ_NODE;
	parent->left = job;
	parent->right = NULL;
	return (parent);
}

t_ASTnode	*gr_seq_3(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*seq;
	t_ASTnode	*job;

	job = GR_job();
	if (job == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	seq = GR_seq();
	if (seq == NULL)
	{
		ASTdelete(job);
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->type = SEQ_NODE;
	parent->left = job;
	parent->right = seq;
	return (parent);
}
/*
** --------------------------------------------------------------
*/

t_ASTnode	*GR_job(void)
{
	t_ASTnode	*node;
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

t_ASTnode	*gr_job_1(void)
{
	return (GR_instr());
}

t_ASTnode	*gr_job_2(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*job;
	t_ASTnode	*instr;

	instr = GR_instr();
	if (instr == NULL)
		return (NULL);
	if (!terminal(PIPE))
	{
		ASTdelete(instr);
		return (NULL);
	}
	job = GR_job();
	if (job == NULL)
	{
		ASTdelete(instr);
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->type = PIPE_NODE;
	parent->left = instr;
	parent->right = job;
	return (parent);
}
/*
** --------------------------------------------------------------
*/

t_ASTnode	*GR_instr(void)
{
	t_tok		*save;
	t_ASTnode	*node;

	save = g_current_tok;
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

t_ASTnode	*gr_instr_1(void)
{
	return (GR_cmd());
}

t_ASTnode	*gr_instr_2(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*cmd;
	char		*filename;

	cmd = GR_cmd();
	if (cmd == NULL)
		return (NULL);
	if (!terminal(REDIR))
	{
		ASTdelete(cmd);
		return (NULL);
	}
	if (g_current_tok->data != NULL)
		filename = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
	{
		ASTdelete(cmd);
		return (return_null(filename));
	}
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->type = REDIR_NODE;
	parent->data = filename;
	parent->left = cmd;
	parent->right = NULL;
	return (parent);
}

t_ASTnode	*gr_instr_3(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*cmd;
	char		*filename;

	cmd = GR_cmd();
	if (cmd == NULL)
		return (NULL);
	if (!terminal(INDIR))
	{
		ASTdelete(cmd);
		return (NULL);
	}
	if (g_current_tok->data != NULL)
		filename = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
	{
		ASTdelete(cmd);
		return (return_null(filename));
	}
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->type = INDIR_NODE;
	parent->data = filename;
	parent->left = cmd;
	parent->right = NULL;
	return (parent);
}

/*
** --------------------------------------------------------------
*/
t_ASTnode	*GR_cmd(void)
{
	t_ASTnode	*node;

	node = gr_cmd_1();
	if (node != NULL)				// dar vuelta a esto?!?!?

		return (node);
	return (NULL);
}

t_ASTnode	*gr_cmd_1(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*tokenlist;
	char		*dataname;

	if (g_current_tok != NULL)
		dataname = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
		return (return_null(dataname));
	tokenlist = GR_tokenlist();
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->type = CMDNAME_NODE;
	parent->data = dataname;
	parent->left = NULL;
	parent->right = tokenlist;
	return (parent);
}

/*
** --------------------------------------------------------------
*/
t_ASTnode	*GR_tokenlist(void)
{
	t_tok		*save;
	t_ASTnode	*node;

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

t_ASTnode	*gr_tokenlist_1(void)
{
	t_ASTnode	*parent;
	t_ASTnode	*tokenlist;
	char		*dataarg;

	if (g_current_tok != NULL)
		dataarg = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
		return (return_null(dataarg));
	tokenlist = GR_tokenlist();
	parent = malloc(sizeof(t_ASTnode));
	if (parent == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	parent->data = dataarg;
	parent->type = TOKEN_NODE;
	parent->left = NULL;
	parent->right = tokenlist;
	return (parent);
}

t_ASTnode	*gr_tokenlist_2(void)
{
	return (NULL);
}
