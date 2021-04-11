/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:50 by rpunet            #+#    #+#             */
/*   Updated: 2021/04/09 23:40:16 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft.h"

# define READ		0
# define WRITE		1
# define BUILTINS	2 // 4

/*
** STRUCTS ---------------------------------
*/
typedef struct s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef struct s_lex
{
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

typedef struct s_ASTnode
{
	int					type;
	char				*data;
	struct s_ASTnode	*left;
	struct s_ASTnode	*right;
}					t_ASTnode;

typedef struct s_cmd
{
	int				io[2];
}					t_cmd;

enum				e_node
{
	SEQ_NODE,
	PIPE_NODE,
	REDIR_NODE,
	INDIR_NODE,
	APPEND_NODE,
	CMDNAME_NODE,
	TOKEN_NODE,
	DATA,
};
/*
** tipo general para comprobaciones de free, etc  
** de los tipos terminales que guardan datos en node->data.
** los demás solo tienen node->type
*/

int			ft_get_input(char **line);
t_tok		*tok_init(int datasize);
void		tok_delete(t_tok *token);

int			ft_lexer(char *line, t_lex *lexer, int size);

int			ft_parser(t_lex *lexer, t_ASTnode **syntax_tree);
void		ASTdelete(t_ASTnode *node);
int			terminal(int	tokentype);
t_ASTnode	*GR_seq(void);
t_ASTnode	*gr_seq_1(void);
t_ASTnode	*gr_seq_2(void);
t_ASTnode	*gr_seq_3(void);
t_ASTnode	*GR_jobvoid(void);
t_ASTnode	*gr_job_1(void);
t_ASTnode	*gr_job_2(void);
t_ASTnode	*GR_instr(void);
t_ASTnode	*gr_instr_1(void);
t_ASTnode	*gr_instr_2(void);
t_ASTnode	*gr_instr_3(void);
t_ASTnode	*GR_cmd(void);
t_ASTnode	*gr_cmd_1(void);
t_ASTnode	*GR_tokenlist(void);
t_ASTnode	*gr_tokenlist_1(void);
t_ASTnode	*gr_tokenlist_2(void);

void		execute_CMD(t_ASTnode *cmd_node, int in, int out);
void		execute_INSTR(t_ASTnode *instr);
void		execute_JOB(t_ASTnode *job);
void		execute_SEQ(t_ASTnode *seq);
void		ft_execute(t_ASTnode *syntax_tree);

int			exit_failure(char *format, ...);

#endif
