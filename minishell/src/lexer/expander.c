/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:38:29 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/23 23:05:32 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_command(t_minishell *shell, char **aux, char **find)
{
	char	*tmp;
	int		i;
	char	*var_value;

	var_value = find_value(shell->envp_dup, *aux);
	i = ft_strchr_pos(shell->lexer.current_tok->data, '$');
	*aux = ft_memfree(*aux, ft_substr(shell->lexer.current_tok->data, 0, i));
	if (var_value)
	{
		tmp = ft_strjoin(*aux, var_value);
		var_value = ft_memfree(var_value, NULL);
		*aux = ft_memfree(*aux, tmp);
	}
	else if (!strcmp(shell->lexer.current_tok->data, "$?"))
	{
		tmp = ft_itoa(get_minishell(NULL)->exit_code);
		*aux = ft_memfree(*aux, tmp);
	}
	shell->lexer.current_tok->data = \
		ft_memfree(shell->lexer.current_tok->data, NULL);
	return (ft_memfree(*aux, ft_strjoin(*aux, *find)));
}

void	expand_vars(void)
{
	char		*find;
	t_minishell	*shell;
	char		*aux;
	int			i;

	shell = get_minishell(NULL);
	find = ft_strchr(shell->lexer.current_tok->data, '$');
	while (find)
	{
		if (++find)
		{
			i = ft_strchr_pos(find, '$');
			if (i != ERROR)
			{
				aux = ft_substr(find, 0, i);
				find += i;
			}
			else
			{
				aux = ft_strdup(find);
				find = '\0';
			}
			shell->lexer.current_tok->data = get_command(shell, &aux, &find);
		}
	}
}
