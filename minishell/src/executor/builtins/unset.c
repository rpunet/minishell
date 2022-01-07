/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:05:03 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/07 10:14:50 by jcarrete         ###   ########.fr       */
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
		ft_dprintf(STDERR_FILENO, "MINIsh: unset: not a valid identifier");
	}
	find = ft_memfree(find, NULL);
	return (shell->exit_code);
}
