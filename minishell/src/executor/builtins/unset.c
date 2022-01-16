/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:05:03 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/16 13:01:46 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char ***envp)
{
	char		*find;
	t_minishell	*shell;
	int			i;

	shell = get_minishell(NULL);
	shell->exit_code = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		find = find_variable(*envp, args[i], NULL);
		if (find)
			delete_var(envp, args[i]);
		find = ft_memfree(find, NULL);
		i++;
	}
	return (shell->exit_code);
}
