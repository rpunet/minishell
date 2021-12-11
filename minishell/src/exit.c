/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:54:49 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/06 10:11:37 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_str(int status)
{
	if (status == E_MEM)
		ft_dprintf(STDERR_FILENO, "Unable to allocate memory: ");
}

void	exit_program(t_minishell *shell, int status, int err, char *extra)
{
	free_program(shell, status);
	if (status == EXIT_SUCCESS)
		exit (EXIT_SUCCESS);
	ft_dprintf(STDERR_FILENO, "ERROR:\n");
	if (err != E_NONE)
		error_str(err);
	if (extra != NULL)
		ft_dprintf(STDERR_FILENO, extra);
	ft_dprintf(STDERR_FILENO, "\n");
	exit(EXIT_FAILURE);
}