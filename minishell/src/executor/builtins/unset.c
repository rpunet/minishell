/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:05:03 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/08 21:01:46 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char ***envp)
{
	char		*find;
	t_minishell	*shell;

	shell = get_minishell(NULL);
	shell->exit_code = EXIT_SUCCESS;
	find = find_variable(*envp, *args, NULL);
	if (*args && find)
		delete_var(envp, *args);
	else
	{
		shell->exit_code = EXIT_FAILURE;
		ft_dprintf(STDOUT_FILENO, "MINIshell: %s: not a valid identifier\n", \
			args[0]);
	}
	find = ft_memfree(find, NULL);
	return (shell->exit_code);
}
