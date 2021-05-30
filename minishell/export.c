/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2021/05/30 22:54:43 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_args_export(char **envp)
{
	char	**print_exp;
	int		i;
	int		j;
	int		len;

	if (!envp)
		return (NULL);
	len = double_len(envp);
	print_exp = ft_memalloc(sizeof(char *) * len);
	if (print_exp == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (envp[i] && ft_strcmp(envp[i], ""))
			print_exp[j++] = ft_strdup(envp[i]);
		i++;
	}
	i = 0;
	while (print_exp[i])
	{
		j = 0;
		while (print_exp[j])
		{
			if (ft_strcmp(print_exp[i], print_exp[j]) < 0)
				ft_swap_str(&(print_exp[i]), &(print_exp[j]));
			j++;
		}
		i++;
	}
	i = 0;
	while (print_exp[i])
	{
		if (!ft_strchr(print_exp[i], "="))
			ft_printf("declare -x %s\n", print_exp[i]);
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_export(char **args, char **envp)
{
	int	i;

	i = 1;
	if (!args[i])
		return (no_args_export(envp));
	return (EXIT_SUCCESS);
}
