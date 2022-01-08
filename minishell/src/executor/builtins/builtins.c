/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2022/01/08 20:17:02 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_len(char **arr)
{
	int	i;

	i = 0;
	if (!*arr || !arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	check_builtins(char **args, char **envp)
{
	if (!ft_strcmp(args[0], "env"))
	{
		while (*envp)
		{
			ft_dprintf(STDOUT_FILENO, "%s\n", *envp);
			envp++;
		}
		return (TRUE);
	}
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args, &envp);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(args, &envp);
	return (FALSE);
}
