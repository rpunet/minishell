/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:47:59 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/07 12:50:49 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, char ***envp)
{
	char		*ret;
	t_minishell	*shell;

	shell = get_minishell(NULL);
	shell->exit_code = EXIT_SUCCESS;
	do_nothing(envp);
	ret = getcwd(NULL, 0);
	if (ret)
	{
		ft_printf("%s\n", ret);
		ret = ft_memfree(ret, NULL);
	}
	else
	{
		shell->exit_code = EXIT_FAILURE;
		ft_dprintf(STDERR_FILENO, "MINIshell: %s: %s\n", args[0], strerror(errno));
	}
	return (shell->exit_code);
}
