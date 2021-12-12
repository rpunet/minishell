/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/12/12 17:29:15 by jcarrete         ###   ########.fr       */
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
	int				i;

	i = 0;
	if (!ft_strcmp(args[0], "env"))
	{
		while (*envp)
		{
			ft_printf("%s\n", *envp);
			envp++;
		}
		return (TRUE);
	}
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args, envp);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(args, envp);
	return (FALSE);
}
