/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:48:44 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/07 10:19:29 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd(char ***envp)
{
	char	*find;
	char	*save;
	char	*dir;

	find = find_variable(*envp, "OLDPWD", NULL);
	delete_var(envp, find);
	save = find_value(*envp, "PWD");
	dir = ft_strjoin("OLDPWD=", save);
	add_single_exp(envp, dir);
	find = ft_memfree(find, find_variable(*envp, "PWD", NULL));
	delete_var(envp, find);
	save = ft_memfree(save, getcwd(NULL, 0));
	dir = ft_memfree(dir, ft_strjoin("PWD=", save));
	add_single_exp(envp, dir);
	find = ft_memfree(find, NULL);
	save = ft_memfree(save, NULL);
	dir = ft_memfree(dir, NULL);
}

int	ft_cd(char **args, char ***envp)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	shell->exit_code = EXIT_SUCCESS;
	if (double_len(args) <= 2)
	{
		if (chdir(args[1]) == -1)
		{
			shell->exit_code = EXIT_FAILURE;
			ft_printf("MINIshell: cd: No such file or directory\n");
		}
		else
			change_pwd(envp);
	}
	else
	{
		shell->exit_code = EXIT_FAILURE;
		ft_printf("MINIshell: cd: too many arguments\n");
	}
	return (shell->exit_code);
}
