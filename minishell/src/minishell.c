/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:45:53 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/15 18:24:37 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_shell(t_minishell *shell, int argc)
{
	ast_delete(&(shell->syntax_tree));
	tok_delete(&((shell->lexer).list_token));
	shell->std.in = shell->save_std.in;
	shell->std.out = shell->save_std.out;
	shell->line = ft_memfree(shell->line, NULL);
	shell->state = ST_PREPARED;
	if (argc > 1)
		return (FALSE);
	return (TRUE);
}

static int	ft_get_input(char **line)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	shell->prompt = set_prompt("$ ");
	*line = readline(shell->prompt);
	shell->prompt = ft_memfree(shell->prompt, NULL);
	if (shell->state == ST_PREPARED)
		shell->state = ST_OK;
	if (*line == NULL)
	{
		null_line();
		return (FALSE);
	}
	add_history(*line);
	return (TRUE);
}

void	initialize_minishell(t_minishell *shell, int argc)
{
	int	condition;

	condition = TRUE;
	shell->state = ST_PREPARED;
	while (condition)
	{
		if (argc == 1)
			condition = ft_get_input(&(shell->line));
		if (condition)
		{
			if (ft_lexer(shell))
				ft_dprintf(STDOUT_FILENO, \
					"MINIshell: Lexer: %s\n", strerror(errno));
			if (!ft_parser(&(shell->lexer), &(shell->syntax_tree)) \
					&& shell->state == ST_OK)
				ft_execute(shell->syntax_tree, &(shell->envp_dup));
			else
			{
				shell->state = ST_ERROR;
				shell->exit_code = E_PARSER;
			}
		}
		condition = reset_shell(shell, argc);
	}
}
