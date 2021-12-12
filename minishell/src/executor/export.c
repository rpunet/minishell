/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/12 16:08:40 by jcarrete         ###   ########.fr       */
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

int	ft_export(t_minishell *shell, char **args, char ***envp)
{
	int		i;
	int		no_deleted;
	char	*find;

	i = 1;
	if (args[i] == NULL)
		return (no_args_export(*envp));
	if (args[1][0] == '-')
		exit_program(NULL, 0, 0, "Export doesn't handle any options\n");
	while (args[i])
	{
		no_deleted = 0;
		shell->exit_code = check_syntax(args[i]);
		if (shell->exit_code == EXIT_FAILURE)
			ft_printf("MINIsh: export:`%s': not a valid identifier\n", args[i]);
		else
		{
			delete_var(envp, find = find_variable(*envp, args[i], &no_deleted));
			if (!no_deleted)
				add_single_exp(envp, args[i]);
		}
		i++;
		find = ft_memfree(find, NULL);
	}
	return (shell->exit_code);
}
