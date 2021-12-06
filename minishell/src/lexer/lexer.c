/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:27:46 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/06 20:41:24 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quote_end(t_lex *lexer, t_tok *token, char *line)
{
	if (lexer->seq_state == S_QUOTED && line[lexer->line_pos] == '\'')
	{
		lexer->last_quoted = TRUE;
		lexer->seq_state = S_GENERAL;
	}
	else if (lexer->seq_state == S_DQUOTED && line[lexer->line_pos] == '\"')
		lexer->seq_state = S_GENERAL;
	else
	{
		token->data[lexer->token_pos] = (char)(line[lexer->line_pos]);
		(lexer->token_pos)++;
	}
}

static void	check_operators(t_lex *lexer, t_tok *token, \
								char *line, char **envp)
{
	if (lexer->token_pos > 0)
	{
		token->data[lexer->token_pos] = 0;
		if (lexer->last_quoted == FALSE)
			expand_vars(&token->data, envp);
		token->next = tok_init(1);
		token = token->next;
		lexer->last_quoted = FALSE;
		lexer->token_pos = 0;
	}
	token->data[0] = (char)(line[lexer->line_pos]);
	token->data[1] = 0;
	token->type = line[lexer->line_pos];
	token->next = tok_init(ft_strlen(line) - lexer->line_pos);
	token = token->next;
}

static void	check_special_chars(t_lex *lexer, t_tok *token, \
								char *line, char **envp)
{
	char	c;

	c = line[lexer->line_pos];
	token->type = T_TOKEN;
	if (c == '\'')
		lexer->seq_state = S_QUOTED;
	else if (c == '\"')
		lexer->seq_state = S_DQUOTED;
	else if (c == '\\')
		token->data[(lexer->token_pos)++] = line[++(lexer->line_pos)];
	else if (c == ' ')
	{
		if (lexer->token_pos > 0)
		{
			token->type = T_NULTOK;
			token->data[lexer->token_pos] = 0;
			if (lexer->last_quoted == FALSE)
				expand_vars(&token->data, envp);
			token->next = tok_init(ft_strlen(line) - lexer->line_pos);
			token = token->next;
			lexer->last_quoted = FALSE;
			lexer->token_pos = 0;
		}
	}
}

static void	check_state(t_lex *lexer, char *line, char **envp)
{
	t_tok	*token;

	token = lexer->list_token;
	if (lexer->seq_state == S_GENERAL)
	{
		if (ft_strchr(SPECIAL_CHARS, line[lexer->line_pos]))
			check_special_chars(lexer, token, line, envp);
		else if (ft_strchr(OPERATORS, line[lexer->line_pos]))
			check_operators(lexer, token, line, envp);
		else
		{
			token->data[lexer->token_pos] = (char)(line[lexer->line_pos]);
			(lexer->token_pos)++;
			token->type = T_TOKEN;
		}
	}
	else if (lexer->seq_state == S_QUOTED || lexer->seq_state == S_DQUOTED)
		check_quote_end(lexer, token, line);
}

int	ft_lexer(t_minishell *shell)
{
	t_lex	*lexer;

	lexer = &(shell->lexer);
	lexer->list_token = tok_init(ft_strlen(shell->line));
	lexer->seq_state = S_GENERAL;
	lexer->last_quoted = FALSE;
	lexer->line_pos = 0;
	lexer->token_pos = 0;
	while (shell->line[lexer->line_pos] != 0)
	{
		check_state(lexer, shell->line, shell->envp_dup);
		(lexer->line_pos)++;
	}
	shell->lexer.list_token->data[lexer->token_pos] = 0;
	if (shell->lexer.last_quoted == FALSE)
		expand_vars(&(shell->lexer.list_token->data), shell->envp_dup);
	return (EXIT_SUCCESS);
}
