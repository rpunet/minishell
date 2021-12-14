/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/15 00:12:26 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	*init_struct(void)
{
	t_minishell	*ret;

	ret = ft_calloc(1, sizeof(t_minishell));
	if (ret == NULL)
		exit_program(ret, F_NONE, E_MEM, strerror(errno));
	get_minishell(ret);
	ret->state = ST_INIT;
	ret->line = NULL;
	ret->lexer.list_token = NULL;
	ret->syntax_tree = NULL;
	ret->envp_dup = NULL;
	ret->exit_code = EXIT_SUCCESS;
	return (ret);
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

static void	initialize_minishell(t_minishell *shell, int argc)
{
	int	condition;

	condition = TRUE;
	while (condition)
	{
		if (argc == 1)
			if (ft_get_input(&(shell->line)))
				continue ;
		printf("holahola\n");
		if (ft_lexer(shell))
			ft_printf("error");
		if (!ft_parser(&(shell->lexer), &(shell->syntax_tree)))
			ft_execute(shell->syntax_tree, &(shell->envp_dup));
		else
			ft_putstr_fd("MINIsh: syntax error near unexpected token `;'\n", 1);
		ast_delete(shell->syntax_tree);
		tok_delete((shell->lexer).list_token);
		shell->line = ft_memfree(shell->line, NULL);
		if (argc > 1)
			condition = FALSE;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	shell = init_struct();
	if (argc > 1 && !ft_strcmp(argv[1], "-c"))
		shell->line = argv[2];
	shell->envp_dup = ft_envdup(envp, double_len(envp), 1, NULL);
	envp = shell->envp_dup;
	set_shell_signals(shell);
	initialize_minishell(shell, argc);
	return (EXIT_SUCCESS);
}
