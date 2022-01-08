/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 22:27:46 by rpunet            #+#    #+#             */
/*   Updated: 2022/01/08 13:00:28 by jcarrete         ###   ########.fr       */
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

static int	check_operators(t_lex *lexer, t_tok **token, \
								char *line, char **envp)
{
	if (lexer->token_pos > 0)
	{
		(*token)->data[lexer->token_pos] = 0;
		if (lexer->last_quoted == FALSE)
			expand_vars(&(*token)->data, envp);
		(*token)->next = tok_init(1);
		if ((*token)->next == NULL)
			return (EXIT_FAILURE);
		(*token) = (*token)->next;
		lexer->last_quoted = FALSE;
		lexer->token_pos = 0;
	}
	(*token)->data[0] = (char)(line[lexer->line_pos]);
	(*token)->data[1] = 0;
	(*token)->type = line[lexer->line_pos];
	(*token)->next = tok_init(ft_strlen(line) - lexer->line_pos);
	if ((*token)->next == NULL)
		return (EXIT_FAILURE);
	(*token) = (*token)->next;
	return (EXIT_SUCCESS);
}

static int	check_special_chars(t_lex *lexer, t_tok **token, \
								char *line, char **envp)
{
	const char	c = line[lexer->line_pos];

	(*token)->type = T_TOKEN;
	if (c == '\'')
		lexer->seq_state = S_QUOTED;
	else if (c == '\"')
		lexer->seq_state = S_DQUOTED;
	else if (c == '\\')
		(*token)->data[(lexer->token_pos)++] = line[++(lexer->line_pos)];
	else if (c == ' ')
	{
		if (lexer->token_pos > 0)
		{
			(*token)->data[lexer->token_pos] = 0;
			if (lexer->last_quoted == FALSE)
				expand_vars(&(*token)->data, envp);
			(*token)->next = tok_init(ft_strlen(line) - lexer->line_pos);
			if ((*token)->next == NULL)
				return (EXIT_FAILURE);
			(*token) = (*token)->next;
			lexer->last_quoted = FALSE;
			lexer->token_pos = 0;
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_state(t_lex *lexer, char *line, char **envp)
{
	t_tok	*token;
	int		ret;

	token = lexer->current_tok;
	ret = EXIT_SUCCESS;
	if (lexer->seq_state == S_GENERAL)
	{
		if (ft_strchr(SPECIAL_CHARS, line[lexer->line_pos]))
			ret = check_special_chars(lexer, &token, line, envp);
		else if (ft_strchr(OPERATORS, line[lexer->line_pos]))
			ret = check_operators(lexer, &token, line, envp);
		else
		{
			token->data[lexer->token_pos] = (char)(line[lexer->line_pos]);
			(lexer->token_pos)++;
			token->type = T_TOKEN;
		}
	}
	else if (lexer->seq_state == S_QUOTED || lexer->seq_state == S_DQUOTED)
		check_quote_end(lexer, token, line);
	lexer->current_tok = token;
	return (ret);
}

int	ft_lexer(t_minishell *shell)
{
	t_lex	*lexer;
	int		ret;

	lexer = &(shell->lexer);
	lexer->current_tok = tok_init(ft_strlen(shell->line));
	if (lexer->current_tok == NULL)
		return (EXIT_FAILURE);
	lexer->list_token = lexer->current_tok;
	lexer->seq_state = S_GENERAL;
	lexer->last_quoted = FALSE;
	lexer->line_pos = 0;
	lexer->token_pos = 0;
	while (shell->line[lexer->line_pos] != 0)
	{
		ret = check_state(lexer, shell->line, shell->envp_dup);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(lexer->line_pos)++;
	}
	shell->lexer.current_tok->data[lexer->token_pos] = 0;
	if (shell->lexer.last_quoted == FALSE)
		expand_vars(&(shell->lexer.current_tok->data), shell->envp_dup);
	return (EXIT_SUCCESS);
}
