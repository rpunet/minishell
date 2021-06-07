/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2021/06/07 23:22:00 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**replace_envp(char **origin, char **new)
{
	int	i;

	i = 0;
	while (origin && origin[i])
	{
		origin[i] = ft_memfree(origin[i], NULL);
		i++;
	}
	if (origin)
		free(origin);
	return (new);
}

static char	**ft_envdup(char **envp, int len)
{
	char	**res;
	int		i;
	int		j;

	res = ft_memalloc(sizeof(char *) * len);
	if (res == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (envp[i] && ft_strcmp(envp[i], ""))
			res[j++] = ft_strdup(envp[i]);
		i++;
	}
	return (res);
}

static int	no_args_export(char **envp)
{
	char	**print_exp;
	int		i;
	int		j;
	int		len;

	if (!envp)
		return (EXIT_SUCCESS);
	len = double_len(envp);
	print_exp = ft_envdup(envp, len);
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
		if (!ft_strchr(print_exp[i], '='))
			ft_printf("declare -x %s\n", print_exp[i]);
		i++;
	}
	free_char_array(print_exp, len);
	return (EXIT_FAILURE);
}

static int	check_syntax(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))
		return (EXIT_FAILURE);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) != 0 && arg[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	add_single_exp(char **envp, char *arg)
{
	int		i;
	int		len;
	char	**print_exp;

	i = 0;
	while (envp[i])
	{
		len = 0;
		while (ft_isdigit(envp[i][0]) == 0 && \
			((ft_isalnum(envp[i][len])) || (envp[i][len] == '_')))
			len++;
		if (!ft_strncmp(envp[i], arg, len))
			return ;
		i++;
	}
	len = double_len(envp);
	print_exp = ft_envdup(envp, len);
	print_exp[len] = ft_strdup(arg);
	envp = replace_envp(envp, print_exp);
}

int	ft_export(char **args, char **envp)
{
	int		i;
	char	*valid;

	i = 1;
	if (!args[i])
		return (no_args_export(envp));
	if (args[1][0] == '-')
		exit_failure("Export doesn't handle any options");
	while (args[i])
	{
		if (check_syntax(args[i]) == EXIT_FAILURE)
			exit_failure("Minishell: export: `%s': \
				not a valid identifier\n", args[i]);
		valid = ft_strchr(args[i], '=');
		if (!valid)
			add_single_exp(envp, args[i]);
		// else
		// 	add_comp_exp(args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
