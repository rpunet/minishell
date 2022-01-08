/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:09:26 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/08 21:00:14 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	ft_dprintf(STDOUT_FILENO, "exit\n");
	if (ft_str_arr_count(argv) == 2)
	{
		if (ft_is_number(argv[1]) == FALSE)
		{
			ft_dprintf(STDOUT_FILENO, \
			"MINIshell: %s: %s: numeric argument required\n", argv[0], argv[1]);
			shell->exit_code = EB_MISUSE_BUILTINS;
		}
		else
			shell->exit_code = ft_atoi(argv[1]) % 256;
	}
	else if (ft_str_arr_count(argv) > 2)
	{
		shell->exit_code = EB_COMMAND_NOT_FOUND;
		ft_dprintf(STDOUT_FILENO, \
			"MINIshell: %s: too many arguments\n", argv[0]);
		return (EXIT_FAILURE);
	}
	exit_program(shell, F_SHELL, E_NONE, NULL);
	return (EXIT_SUCCESS);
}
