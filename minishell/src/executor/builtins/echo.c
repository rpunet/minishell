/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:47:08 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/12 23:44:42 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args, char ***envp)
{
	int	i;

	do_nothing(envp);
	if (!args[1])
		write(1, "\n", 1);
	else
	{
		i = 1;
		if (!ft_strcmp(args[1], "-n"))
			i++;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(args[1], "-n"))
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
