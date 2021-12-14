/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 16:09:26 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/15 00:25:26 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(void)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	ft_printf("exit", STDOUT_FILENO);
	exit_program(shell, F_SHELL, E_NONE, "");
	return (EXIT_SUCCESS);
}
