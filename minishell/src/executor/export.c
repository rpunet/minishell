/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/08 18:21:15 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
		return (EXIT_FAILURE);
	while (arg[i] && arg[i] != '=')
	{
		if ((ft_isalnum(arg[i]) == 0) && (arg[i] != '_'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	export_variable(char **args, char ***envp, int i)
{
	int		no_deleted;
	char	*find;

	no_deleted = 0;
	delete_var(envp, find = find_variable(*envp, args[i], &no_deleted));
	if (!no_deleted)
		add_single_exp(envp, args[i]);
	find = ft_memfree(find, NULL);
}

int	ft_export(char **args, char ***envp)
{
	int			i;
	t_minishell	*shell;

	shell = get_minishell(NULL);
	shell->exit_code = EXIT_SUCCESS;
	i = 1;
	if (args[i] == NULL)
		shell->exit_code = no_args_export(*envp);
	else if (args[1][0] == '-')
	{
		shell->exit_code = EXIT_FAILURE;
		ft_dprintf(STDOUT_FILENO, "MINIshell: %s:`%s': \
			invalid option\n", args[0], args[1]);
	}
	while (args[i] && shell->exit_code == EXIT_SUCCESS)
	{
		shell->exit_code = check_syntax(args[i]);
		if (shell->exit_code == EXIT_FAILURE)
			ft_dprintf(STDOUT_FILENO, "MINIshell: %s:`%s': \
				not a valid identifier\n", args[0], args[i]);
		else
			export_variable(args, envp, i);
		i++;
	}
	return (shell->exit_code);
}
