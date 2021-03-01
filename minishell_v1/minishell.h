/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:50 by rpunet            #+#    #+#             */
/*   Updated: 2021/03/01 11:48:58 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../../libftPLUS/includes/libft.h"

# define READ		0
# define WRITE		1
# define BUILTINS	2 // 4

// STRUCTS   --------------------------------
typedef struct		s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_lex
{
	//int				n_tokens;
	t_tok			*list_token;
}					t_lex;

enum				e_tok{
	TOKEN = -1,
	SEMICOLON = ';',
	SPACE = ' ',
	PIPE = '|',
	REDIR = '>',
	INDIR = '<',
	APPEND = 66,
	QUOTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	NULTOK = 0,
};

enum				e_seq{
	GENERAL,
	QUOTED,
	DQUOTED,
	SCAPED,
};

typedef struct		s_ASTnode
{
	int				type;
	char			*data;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}					t_ASTnode;

enum				e_node
{
	SEQ,
	PIPE,
	REDIR,
	INDIR,
	APPEND,
	CMDPATH,
	TOKEN,
	DATA,				// tipo general para comprobaciones de free, etc   de los tipos terminales que guardan datos en node->data. los demás solo tienen node->type
};


int		ft_lexer(char *line, t_lex *lexer, int size);
int		main(int argc, char **argv);

#endif