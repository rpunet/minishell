/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:18:27 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/09 16:31:31 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_array(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = ft_memfree(arr[i], NULL);
		i++;
	}
	arr = ft_memfree(arr, NULL);
}

void	free_program(t_minishell *shell, int status)
{
	if (status >= F_SHELL)
	{
		if (shell->line != NULL)
			shell->line = ft_memfree(shell->line, NULL);
		if (shell->envp_dup != NULL)
			free_char_array(shell->envp_dup, ft_str_arr_count(shell->envp_dup));
		if (shell->syntax_tree != NULL)
			ast_delete(&(shell->syntax_tree));
		tok_delete(&((shell->lexer).list_token));
		close(shell->std.in);
		close(shell->std.out);
		shell = ft_memfree(shell, NULL);
	}
}
