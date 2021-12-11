/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:18:27 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/04 21:22:13 by jcarrete         ###   ########.fr       */
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
		shell = ft_memfree(shell, NULL);
}
