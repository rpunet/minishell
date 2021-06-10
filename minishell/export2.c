/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2021/06/10 21:46:23 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
*/
static char	**ft_envdup(char **envp, int len, int add)
{
	char	**res;
	int		i;
	int		j;

	res = ft_memalloc(sizeof(char *) * (len + add));
	if (res == NULL)
		exit_failure("Unable to allocate memory: %s\n", strerror(errno));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (envp[i] && ft_strcmp(envp[i], ""))
		{
			res[j] = ft_strdup(envp[i]);
			j++;
		}
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
	print_exp = ft_envdup(envp, len, 1);
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
	while (i < len)
	{
		if (print_exp[i][0] != '_')					// la ultima variable _ no se imprime en export por lo que veo
		{
			j = 0;
			if (ft_strchr((print_exp[i]), '='))
			{
				ft_putstr_fd("declare -x ", 1);					// todo esto es porque export saca formato con comillas: key="value"
				while (print_exp[i][j] != '=')
					j++;
				write(1, print_exp[i], j + 1);
				write(1, "\"", 1);
				ft_printf("%s", &print_exp[i][j + 1]);
				write(1, "\"\n", 2);
			}
		}
		i++;
	}
	free_char_array(print_exp, len);
	return (EXIT_FAILURE);
}

static int	check_syntax(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]))			// mas bien seria que sea solo alfabetico, tmpoco valen signos
		return (EXIT_FAILURE);
	while (arg[i] && arg[i] != '=')
	{
		if ((ft_isalnum(arg[i]) == 0) && (arg[i] != '_'))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	add_single_exp(char **envp, char *arg)
{
	// int		i;
	int		len;
	char	**print_exp;

	// i = 0;
	// while (envp[i])
	// {
	// 	len = 0;
	// 	while (ft_isdigit(envp[i][0]) == 0 && ((ft_isalnum(envp[i][len])) || (envp[i][len] == '_')))
	// 		len++;
	// 	if (!ft_strncmp(envp[i], arg, len))
	// 		return ;
	// 	i++;
	// }
	len = double_len(envp);
	print_exp = ft_envdup(envp, len, 2);
	print_exp[len] = ft_strdup(arg);			// copia todo de momento, en realidad caracteres especiaes no tiene que copiar
	//envp = replace_envp(envp, print_exp);
	envp = print_exp;
	// while (*envp)
	// {
	// 	ft_printf("%s\n", *envp);
	// 	envp++;
	// }
	while (*print_exp)
	{
		ft_printf("%s\n", *print_exp);
		print_exp++;
	}
}

int	ft_export(char **args, char **envp)
{
	int		i;
	// char	*valid;
	int		exit;

	i = 1;
	if (!args[i])
		return (no_args_export(envp));
	if (args[1][0] == '-')
		exit_failure("Export doesn't handle any options\n");
	exit = 0;
	while (args[i])
	{
		if (check_syntax(args[i]) == EXIT_FAILURE)		// no retornamos aqui, aunqu haya errores sintacticos, las que estan bien si que se exportan
			exit = 1;
		// valid = ft_strchr(args[i], '=');
		// if (!valid)
		else
			add_single_exp(envp, args[i]);
		// else
		// 	add_comp_exp(args[i]);
		i++;
	}
	return (exit);
}
