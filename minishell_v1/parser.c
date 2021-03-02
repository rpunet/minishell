/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:36:14 by rpunet            #+#    #+#             */
/*   Updated: 2021/03/02 21:18:41 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
----------shell grammar rules:---------------

SEQUENCE		:=		JOB	;	SEQUENCE
						JOB	;
						JOB

JOB				:=		INSTR
						INSTR	|	JOB

INSTR			:=		CMD
						CMD		>	filename
						CMD		<	filename
						CMD		>>	filename			¿¿cómo incluir varias >  > ?? el test lo prueba

CMD				:=		cmdname	TOKENLIST

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
	g_current_tok = g_current_tok->next;
	return (0);
}
// -----------------------------------------------------------------------------------------------
t_ASTnode	*GR_seq()
{
	t_ASTnode	*node;
	t_tok		*save;

	save = g_current_tok;
	if ((node = gr_seq_3()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_seq_2()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_seq_1()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_seq_1()
{
	return (GR_job());
}

t_ASTnode	*gr_seq_2()
{
	t_ASTnode	*parent;
	t_ASTnode	*job;

	if ((job = GR_job()) == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));  // CHECK MALLOC--> AQUI O EN UNA FUNCION PARA DAR LOS VALORES AL NODO
	parent->type = SEQ_NODE;
	parent->left = job;
	parent->right = NULL;
	return (parent);
}

t_ASTnode	*gr_seq_3()
{
	t_ASTnode	*parent;
	t_ASTnode	*seq;
	t_ASTnode	*job;

	if ((job = GR_job()) == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	if ((seq = GR_seq()) == NULL)
	{
		ASTdelete(job);
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	parent->type = SEQ_NODE;
	parent->left = job;
	parent->right = seq;
	return (parent);
}
// ----------------------------------------------------------------------------------------------

t_ASTnode	*GR_job()
{
	t_ASTnode	*node;
	t_tok		*save;

	save = g_current_tok;
	if ((node = gr_job_2()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_job_1()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_job_1()
{
	return (GR_instr());
}

t_ASTnode	*gr_job_2()
{
	t_ASTnode	*parent;
	t_ASTnode	*job;
	t_ASTnode	*instr;

	if ((instr = GR_instr()) == NULL)
		return (NULL);
	if (!terminal(PIPE))
	{
		ASTdelete(instr);
		return (NULL);
	}
	if ((job = GR_job()) == NULL)
	{
		ASTdelete(instr);
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	parent->type = PIPE_NODE;
	parent->left = instr;
	parent->right = job;
	return (parent);

}
// ----------------------------------------------------------------------------------------------

t_ASTnode	*GR_instr()
{
	t_tok		*save;
	t_ASTnode	*node;

	save = g_current_tok;
	if ((node = gr_instr_3()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_instr_2()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_instr_1()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_instr_1()
{
	return (GR_cmd());
}

t_ASTnode	*gr_instr_2()
{
	t_ASTnode	*parent;
	t_ASTnode	*cmd;
	char		*filename;

	if ((cmd = GR_cmd()) == NULL)
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
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	parent->type = REDIR_NODE;
	parent->data = filename;
	parent->left = cmd;
	parent->right = NULL;
	return (parent);
}

t_ASTnode	*gr_instr_3()
{
	t_ASTnode	*parent;
	t_ASTnode	*cmd;
	char		*filename;

	if ((cmd = GR_cmd()) == NULL)
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
		return (NULL);
	}
	parent = malloc(sizeof(t_ASTnode));
	parent->type = INDIR_NODE;
	parent->data = filename;
	parent->left = cmd;
	parent->right = NULL;
	return (parent);
}

// ----------------------------------------------------------------------------------------------
t_ASTnode	*GR_cmd()
{
	t_ASTnode	*node;

	if ((node = gr_cmd_1()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_cmd_1()
{
	t_ASTnode	*parent;
	t_ASTnode	*tokenlist;
	char		*dataname;

	if (g_current_tok != NULL)
		dataname = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
		return (NULL);
	tokenlist = GR_tokenlist();
		// aqui no chequeo NULL por que NULL es válido (vacío)
	parent = malloc(sizeof(t_ASTnode));
	parent->type = CMDNAME_NODE;
	parent->data = dataname;
	parent->left = NULL;
	parent->right = tokenlist;
	return (parent);
}
// ----------------------------------------------------------------------------------------------
t_ASTnode	*GR_tokenlist()
{
	t_tok		*save;
	t_ASTnode	*node;

	save = g_current_tok;
	if ((node = gr_tokenlist_1()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_tokenlist_2()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_tokenlist_1()
{
	t_ASTnode	*parent;
	t_ASTnode	*tokenlist;
	char		*dataarg;

	if (g_current_tok != NULL)
		dataarg = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
		return (NULL);
	tokenlist = GR_tokenlist();
		// aqui tampoco chequeo NULL por que NULL es válido (vacío)
	parent = malloc(sizeof(t_ASTnode));
	parent->data = dataarg;
	parent->type = TOKEN_NODE;
	parent->left = NULL;
	parent->right = tokenlist;
	return (parent);
}

t_ASTnode	*gr_tokenlist_2()
{
	return (NULL);
}

int		ft_parser(t_lex *lexer, t_ASTnode **syntax_tree)
{
	// error check
	g_current_tok = lexer->list_token;
	*syntax_tree = GR_seq();
	//check errors
	if (g_current_tok != NULL && g_current_tok->type != NULTOK)
		return (1);
	return (0);
}
