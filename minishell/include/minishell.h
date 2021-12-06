/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:50 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/06 20:38:31 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** LIBRARIES ---------------------------------
*/

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"

/*
** DEFINES ---------------------------------
*/

# define READ			0
# define WRITE			1
# define BUILTINS		2

# define TRUE			1
# define FALSE			0

# define EXIT_STATUS	128

# define OPERATORS		";><|()"
# define SPECIAL_CHARS	"\'\"\\ "

/*
** ENUMS ---------------------------------
*/

enum	e_tok
{
	T_TOKEN = -1,
	T_SEMICOLON = ';',
	T_SPACE = ' ',
	T_PIPE = '|',
	T_REDIR = '>',
	T_INDIR = '<',
	T_APPEND = 66,
	T_QUOTE = '\'',
	T_DQUOTE = '\"',
	T_ESCAPE = '\\',
	T_VARIABLE = '$',
	T_NULTOK = 0,
};

enum	e_seq
{
	S_GENERAL,
	S_QUOTED,
	S_DQUOTED,
	S_VAR,
	S_SCAPED,
};

enum	e_pipe
{
	P_IN,
	P_OUT
};

enum	e_node
{
	SEQ_NODE,
	PIPE_NODE,
	REDIR_NODE,
	INDIR_NODE,
	APPEND_NODE,
	CMDNAME_NODE,
	TOKEN_NODE
};

enum	e_state
{
	ST_INIT = 1,
	ST_SIGINT,
};

enum	e_free
{
	F_NONE,
	F_SHELL,
};

enum	e_error
{
	E_NONE,
	E_MEM,
	E_SIG,
	E_EXIT
};

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
	int				line_pos;
	int				token_pos;
	int				seq_state;
	int				last_quoted;
	t_tok			*current_tok;
	t_tok			*list_token;
}					t_lex;

typedef struct s_pipe
{
	int				in;
	int				out;
}					t_pipe;

typedef struct s_ast_node
{
	int					type;
	char				*data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}					t_ast_node;

typedef struct s_cmd
{
	int				io[2];
}					t_cmd;

typedef struct s_minishell
{
	int				state;
	int				exit_code;
	char			*line;
	t_pipe			std;
	t_lex			lexer;
	t_ast_node		*syntax_tree;
	char			**envp_dup;
}					t_minishell;

/*
** tipo general para comprobaciones de free, etc
** de los tipos terminales que guardan datos en node->data.
** los demás solo tienen node->type
*/

t_tok		*g_current_tok;

/*
** MINISHELL ---------------------------------
*/

int			double_len(char **arr);
void		exit_program(t_minishell *shell, int status, int err, char *extra);
char		*find_directory(DIR **dir, char **args);
void		free_program(t_minishell *shell, int status);
void		free_char_array(char **arr, int size);
char		**ft_envdup(char **envp, int len, int add, char *ignore);
t_minishell	*get_minishell(t_minishell *minishell);
void		do_nothing(void *vd);
void		*return_null(char *ptr);
void		set_shell_signals(t_minishell *shell);

/*
** PARSER ------------------------------------
*/

int			ft_parser(t_lex *lexer, t_ast_node **syntax_tree);
void		ast_delete(t_ast_node *node);
int			terminal(int tokentype);
t_ast_node	*gr_seq(void);
t_ast_node	*gr_seq_1(void);
t_ast_node	*gr_seq_2(void);
t_ast_node	*gr_seq_3(void);
t_ast_node	*gr_job(void);
t_ast_node	*gr_job_1(void);
t_ast_node	*gr_job_2(void);
t_ast_node	*gr_instr(void);
t_ast_node	*gr_instr_1(void);
t_ast_node	*gr_instr_2(void);
t_ast_node	*gr_instr_3(void);
t_ast_node	*gr_cmd(void);
t_ast_node	*gr_cmd_1(void);
t_ast_node	*gr_tokenlist(void);
t_ast_node	*gr_tokenlist_1(void);
t_ast_node	*gr_tokenlist_2(void);

/*
** LEXER -------------------------------------
*/

void		expand_vars(char **cmd, char **envp);
char		*find_value(char **envp, char *key);
int			ft_lexer(t_minishell *shell);
t_tok		*tok_init(int datasize);
void		tok_delete(t_tok *token);

/*
** EXECUTOR ----------------------------------
*/

void		add_single_exp(char ***envp, char *arg);
int			check_builtins(char **args, char **envp);
void		delete_var(char ***envp, char *del);
int			exec_process(char **args, char **envp, int i);
void		execute_CMD(t_ast_node *cmd_node, int in, \
							int out, char ***envp, int *fds);
void		execute_INSTR(t_ast_node *instr, char ***envp, int *fds);
void		execute_JOB(t_ast_node *job, char ***envp);
void		execute_SEQ(t_ast_node *seq, char ***envp);
char		*find_variable(char **envp, char *arg, int *no_del);
int			ft_cd(char **args, char ***envp);
int			ft_echo(char **args, char **envp);
void		ft_execute(t_ast_node *syntax_tree, char ***envp);
int			ft_exit(void);
int			ft_export(char **args, char ***envp);
int			ft_unset(char **args, char ***envp);
int			ft_pwd(char **arg, char **envp);
char		*read_key(char *var);
#endif
