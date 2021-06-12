/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 23:04:31 by jcarrete          #+#    #+#             */
/*   Updated: 2021/06/12 04:53:06 by rpunet           ###   ########.fr       */
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

int		check_ignore(char *envp, char *ignore)
{
	char	*key = read_key(envp);

	if (ignore)
	{
		if (!ft_strcmp(key, ignore))
		{
			free(key);
			return (1);
		}
	}
	return (0);
}

char	**ft_envdup(char **envp, int len, int add, char *ignore)
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
		if (envp[i] && ft_strcmp(envp[i], "") && !check_ignore(envp[i], ignore))
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
	int		i;
	int		j;
	int		len;

	if (!envp)
		return (EXIT_SUCCESS);
	len = double_len(envp);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) < 0)
				ft_swap_str(&(envp[i]), &(envp[j]));
			j++;
		}
		i++;
	}
	i = 0;
	while (i < len)
	{
		if (envp[i][0] != '_')					// la ultima variable _ no se imprime en export por lo que veo
		{
			j = 0;
			{
				ft_putstr_fd("declare -x ", 1);					// todo esto es porque export saca formato con comillas: key="value"
				if (ft_strchr((envp[i]), '='))
				{
					while (envp[i][j] != '=')
						j++;
					write(1, envp[i], j + 1);
					ft_printf("\"%s\"\n", &envp[i][j + 1]);			// A VER SI METES TODO EN UN PRINT, NO SE COMO DELIMITAR LA LONGITUD A IMPRIMIR DEL PUNTERO
				}
				else
				ft_printf("%s\n", envp[i]);

			}
		}
		i++;
	}
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



void	add_single_exp(char ***envp, char *arg)
{
	int		len;
	char	**print_exp;
	char	**aux;

	len = double_len(*envp);
	print_exp = ft_envdup(*envp, len, 2, NULL);
	print_exp[len] = ft_strdup(arg);			// copia todo de momento, en realidad caracteres especiaes no tiene que copiar
	aux = *envp;
	*envp = print_exp;
	free_char_array(aux, len);
}

void	delete_var(char ***envp, char *del)
{
	char	**new_envp;
	char	**aux;
	int		len;

	if (del == NULL)
		return ;
	len = double_len(*envp);
	new_envp = ft_envdup(*envp, len, 0, del);
	aux = *envp;
	*envp = new_envp;
	free_char_array(aux, len);
}

char	*read_key(char *var)
{
	int	len;

	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	return (ft_substr(var, 0, len));
}

char	*find_variable(char **envp, char *arg, int *no_add, int del_on)
{
	int		len;
	char	*find;
	char	*key;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	find = ft_substr(arg, 0, len);			//falta liberarlo al final porque esta metida la funcion find variable directamente como argumento. Para probarlo, ejecutar un export x y luego un comando fallido
	while (*envp)
	{
		key = read_key(*envp);
		if (!ft_strcmp(key, find))
		{
			if (!((*envp)[len] == '=' && !arg[len] && !del_on))			// esto es para que si la variable que sustituye es solo x (sin x=3), no sustituya nada.
			{
				free(find);
				return (key);
			}
			if (no_add)
				*no_add = 1;
		}
		free(key);
		envp++;
	}
	free(find);
	return (NULL);
}

int	ft_export(char **args, char ***envp)
{
	int		i;
	int		exit;
	int		no_add = 0;

	i = 1;
	if (!args[i])
		return (no_args_export(*envp));
	if (args[1][0] == '-')
		exit_failure("Export doesn't handle any options\n");
	exit = 0;
	while (args[i])
	{
		if (check_syntax(args[i]) == EXIT_FAILURE)		// no retornamos aqui, aunqu haya errores sintacticos, las que estan bien si que se exportan
			exit = 1;
		else
		{
			delete_var(envp, find_variable(*envp, args[i], &no_add, 0));
			if (!no_add)
				add_single_exp(envp, args[i]);
		}
		i++;
	}
	return (exit);
}

int	ft_unset(char **args, char ***envp)
{
	if (*args && find_variable(*envp, *args, NULL, 1))		//solo va con un unset, FALTA añadir que haga varias a la vez
		delete_var(envp, *args);
	return 0;
}
