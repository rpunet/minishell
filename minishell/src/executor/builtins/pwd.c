/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:47:59 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/07 10:22:28 by jcarrete         ###   ########.fr       */
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
	if (double_len(args) == 1)
	{
		ret = getcwd(NULL, 0);
		ft_printf("%s\n", ret);
		ret = ft_memfree(ret, NULL);
	}
	else
	{
		shell->exit_code = EXIT_FAILURE;
		ft_printf("MINIshell: pwd: too many arguments\n");
	}
	return (shell->exit_code);
}
