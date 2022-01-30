/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 13:28:18 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/30 19:08:09 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	look_for_delim(char tmp, const char *delim)
{
	int		i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] != tmp)
			i++;
		else
			break ;
	}
	return (delim[i]);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*stack = NULL;
	char		*ptr;
	int			flag;

	ptr = NULL;
	flag = FALSE;
	if (str != NULL)
		stack = str;
	while (*stack != '\0')
	{
		if (!flag && *stack != look_for_delim(*stack, delim))
		{
			flag = TRUE;
			ptr = stack;
		}
		else if (flag && *stack == look_for_delim(*stack, delim))
		{
			*stack = '\0';
			stack++;
			break ;
		}
		stack++;
	}
	return (ptr);
}
