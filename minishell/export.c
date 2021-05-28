/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2021/05/29 00:40:13 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_args_export(char **env)
{
	char	**print_exp;
	int		i;
	int		j;

	if (!env)
		return (NULL);
	print_exp = ft_memalloc(sizeof(char *)/* * env.count*/);
	if (print_exp == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	
	//COPIAR VARIABLES ENV
	i = 0;
	j = 0;
	while (i /*< env.count*/)
	{
		if (env[i] && ft_strcmp(env[i], ""))
			print_exp[j++] = ft_strdup(env[i]);
		i++;
	}

	//SORT VARIABLES
	i = 0;
	while (print_exp[i])
	{
		j = 0;
		while(print_exp[j])
		{
			if (ft_strcmp(print_exp[i], print_exp[j]) < 0)
				ft_swap_str(&(print_exp[i]), &(print_exp[j]));
			j++;
		}
		i++;
	}

	//PRINT VARIABLES
	i = 0;
	while (print_exp[i])
	{
		if (!ft_strchr(print_exp[i], "="))
			ft_printf("declare -x %s\n", print_exp[i]);
		i++;
	}
	/*GESTIONAR POSIBLE ERROR EN EL PROCESO??*/
	return (EXIT_FAILURE);
}

int	ft_export(char **args, char **env)
{
	int	i;

	i = 1;
	if (!args[i])
		return (no_args_export(env));
	return (EXIT_SUCCESS);
}
