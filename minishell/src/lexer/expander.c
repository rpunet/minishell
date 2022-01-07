/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:38:29 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/04 21:42:36 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_command(char **var_value, char **cmd, int i, char **aux)
{
	char	*new_cmd;

	new_cmd = malloc(i + ft_strlen(*var_value));
	if (new_cmd == NULL)
		return (free(*var_value));
	new_cmd = ft_memmove(new_cmd, *cmd, i);
	*aux = new_cmd;
	new_cmd = ft_memmove(new_cmd + (i), \
				*var_value, ft_strlen(*var_value));
	*cmd = ft_memfree(*cmd, *aux);
}

void	expand_vars(char **cmd, char **envp)
{
	char	*var_value;
	char	*aux;
	int		i;
	char	*find;

	find = ft_strchr(*cmd, '$');
	if (find)
	{
		find++;
		if (find)
		{
			var_value = find_value(envp, find);
			i = ft_strlen(*cmd) - ft_strlen(find) - 1;
			if (var_value)
				new_command(&var_value, &(*cmd), i, &aux);
			else if (!strcmp(*cmd, "$?"))
			{
				aux = ft_itoa(get_minishell(NULL)->exit_code);
				*cmd = ft_memfree(*cmd, aux);
			}
			else
				*cmd = ft_memfree(*cmd, ft_substr(*cmd, 0, i));
			var_value = ft_memfree(var_value, NULL);
		}
	}
}
