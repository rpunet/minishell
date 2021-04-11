/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:54:49 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/09 22:07:21 by jcarrete         ###   ########.fr       */
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

int	exit_failure(char *format, ...)
{
	ft_dprintf(STDERR_FILENO, "ERROR:\n");
	ft_dprintf(STDERR_FILENO, format);
	exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
