/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:45:53 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/03 19:12:03 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_shell(t_minishell *shell)
{
	ast_delete(&(shell->syntax_tree));
	tok_delete(&((shell->lexer).list_token));
	shell->line = ft_memfree(shell->line, NULL);
}

static int	ft_get_input(char **line)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	shell->prompt = set_prompt("$");
	*line = readline(shell->prompt);
	shell->prompt = ft_memfree(shell->prompt, NULL);
	if (*line == NULL)
	{
		null_line();
		return (EXIT_FAILURE);
	}
	add_history(*line);
	return (EXIT_SUCCESS);
}

void	initialize_minishell(t_minishell *shell, int argc)
{
	int	condition;

	condition = TRUE;
	while (condition)
	{
		if (argc == 1)
			if (ft_get_input(&(shell->line)))
				continue ;
		if (ft_lexer(shell))
			ft_printf("error");
		if (!ft_parser(&(shell->lexer), &(shell->syntax_tree)))
			ft_execute(shell->syntax_tree, &(shell->envp_dup));
		else
		{
			shell->state = ST_ERROR;
			shell->exit_code = E_PARSER;
		}
		//ft_printf("Reseting shell\n");
		reset_shell(shell);
		//condition = FALSE;
		if (argc > 1)
			condition = FALSE;
	}
}
