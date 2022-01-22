/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:54:49 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/22 18:48:00 by rpunet           ###   ########.fr       */
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
	int			ex;
	t_minishell	*tshell;

	tshell = get_minishell(shell);
	ex = tshell->exit_code;
	free_program(tshell, status);
	if (status == EXIT_SUCCESS)
		exit (ex);
	if (err != E_NONE)
	{
		ft_dprintf(STDERR_FILENO, "ERROR:\n");
		error_str(err);
	}
	if (extra != NULL)
		ft_dprintf(STDERR_FILENO, "%s\n", extra);
	exit(ex);
}
