/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:09:26 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/04 22:32:59 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	ft_dprintf(STDOUT_FILENO, "exit");
	if (ft_str_arr_count(argv) > 1)
	{
		if (ft_is_number(argv[1]) == FALSE)
		{
			ft_dprintf(STDERR_FILENO, "exit: numeric argument required\n");
			shell->exit_code = EB_MISUSE_BUILTINS;
		}
		else
		{
			shell->exit_code = ft_atoi(argv[1]) % 256;
			if (ft_str_arr_count(argv) > 2)
			{
				ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
				return (EXIT_FAILURE);
			}
		}
	}
	exit_program(shell, F_SHELL, E_NONE, "");
	return (EXIT_SUCCESS);
}
