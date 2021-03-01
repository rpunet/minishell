/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:36:14 by rpunet            #+#    #+#             */
/*   Updated: 2021/03/01 17:12:46 by rpunet           ###   ########.fr       */
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
	g_current_tok = g_current_tok->next;
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
	t_ASTnode	*main;
	t_ASTnode	*job;

	if ((job = GR_job()) == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	main = malloc(sizeof(t_ASTnode *));  // CHECK MALLOC--> AQUI O EN UNA FUNCION PARA DAR LOS VALORES AL NODO
	main->type = SEQ_NODE;
	main->left = job;
	main->right = NULL;
	return (main);
}

t_ASTnode	*gr_seq_3()
{
	t_ASTnode	*main;
	t_ASTnode	*seq;
	t_ASTnode	*job;

	if ((job = GR_job()) == NULL)
		return (NULL);
	if (!terminal(SEMICOLON))
	{
		ASTdelete(job);
		return (NULL);
	}
	if ((seq == GR_seq()) == NULL)
	{
		ASTdelete(job);
		return (NULL);
	}
	main = malloc(sizeof(t_ASTnode *));
	main->type = SEQ_NODE;
	main->left = job;
	main->right = seq;
	return (main);
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

t_ASTnode	*gr_job_1()
{
	return (GR_instr());
}

t_ASTnode	*gr_job_2()
{
	t_ASTnode	*main;
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
	main = malloc(sizeof(t_ASTnode *));
	main->type = PIPE_NODE;
	main->left = instr;
	main->right = job;
	return (main);

}
// ----------------------------------------------------------------------------------------------

t_ASTnode	*GR_instr()
{
	t_tok		*save;
	t_ASTnode	*node;

	save = g_current_tok;
	if ((node = gr_instr_1()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_instr_2()) != NULL)
		return (node);
	g_current_tok = save;
	if ((node = gr_instr_3()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_instr_1()
{
	return (GR_cmd());
}

t_ASTnode	*gr_instr_2()
{
	t_ASTnode	*main;
	t_ASTnode	*cmd;
	char		*filename;

	if ((cmd = GR_cmd()) == NULL)
		return (NULL);
	if (!terminal(REDIR));
	{
		ASTdelete(cmd);
		return (NULL);
	}
	if (g_current_tok->data != NULL)
		filename = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN));
	{
		ASTdelete(cmd);
		return (NULL);
	}
	main = malloc(sizeof(t_ASTnode *));
	main->type = REDIR_NODE;
	main->data = filename;
	main->left = cmd;
	main->right = NULL;
	return (main);
}

t_ASTnode	*gr_instr_3()
{
	t_ASTnode	*main;
	t_ASTnode	*cmd;
	char		*filename;

	if ((cmd = GR_cmd()) == NULL)
		return (NULL);
	if (!terminal(INDIR));
	{
		ASTdelete(cmd);
		return (NULL);
	}
	if (g_current_tok->data != NULL)
		filename = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN));
	{
		ASTdelete(cmd);
		return (NULL);
	}
	main = malloc(sizeof(t_ASTnode *));
	main->type = INDIR_NODE;
	main->data = filename;
	main->left = cmd;
	main->right = NULL;
	return (main);
}

// ----------------------------------------------------------------------------------------------
t_ASTnode	*GR_cmd()
{
	t_tok		*save;
	t_ASTnode	*node;

	save = g_current_tok;
	if ((node = gr_cmd_1()) != NULL)
		return (node);
	return (NULL);
}

t_ASTnode	*gr_cmd_1()
{
	t_ASTnode	*main;
	t_ASTnode	*tokenlist;
	char		*datapath;

	if (g_current_tok->data != NULL)
		datapath = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
		return (NULL);
	tokenlist = GR_tokenlist();
		// aqui no chequeo NULL por que NULL es válido (vacío)
	main = malloc(sizeof(t_ASTnode *));
	main->type = CMDPATH_NODE;
	main->data = datapath;
	main->left = NULL;
	main->right = tokenlist;
	return (main);
}
// ----------------------------------------------------------------------------------------------
t_ASTnode	*GR_tokenlist()
{
	t_tok		*save;
	t_ASTnode	*node;

	save = g_current_tok;
	if ((node = gr_tokenlist_1() != NULL))
		return (node);
	g_current_tok = save;
	if ((node = gr_tokenlist_2() != NULL))
		return (node);
	return (NULL);
}

t_ASTnode	*gr_tokenlist_1()
{
	t_ASTnode	*main;
	t_ASTnode	*tokenlist;
	char		*data;

	if (g_current_tok->data != NULL)
		data = ft_strdup(g_current_tok->data);
	if (!terminal(TOKEN))
		return (NULL);
	tokenlist = GR_tokenlist();
		// aqui tampoco chequeo NULL por que NULL es válido (vacío)
	main = malloc(sizeof(t_ASTnode *));
	main->data = data;
	main->type = TOKEN_NODE;
	main->left = NULL;
	main->right = tokenlist;
	return (main);
}

t_ASTnode	*gr_tokenlist_2()
{
	return (NULL);
}

int		parser(t_lex *lexer, t_ASTnode **syntax_tree)
{
	// error check
	g_current_tok = lexer->list_token;
	*syntax_tree = GR_seq();
	//check errors
	if (g_current_tok != NULL && g_current_tok->type != NULTOK)
		return (1);
	return (0);
}
