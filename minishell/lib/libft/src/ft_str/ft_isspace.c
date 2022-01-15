/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:42:10 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/12 20:52:59 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_iteris(char *str, int (*f)(int))
{
	int	i;

	i = 0;
	while (str[i])
		if (f(str[i++]) == 0)
			return (0);
	return (1);
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
