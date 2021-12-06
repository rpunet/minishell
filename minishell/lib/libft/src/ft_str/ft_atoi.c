/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:35:55 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:54:02 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	atoi;

	i = 0;
	s = 1;
	atoi = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		atoi *= 10;
		atoi += str[i] - 48;
		i++;
	}
	return (atoi * s);
}

long	ft_atol(const char *str)
{
	int		i;
	int		s;
	long	atol;

	i = 0;
	s = 1;
	atol = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			s = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		atol *= 10;
		atol += str[i] - 48;
		i++;
	}
	return (atol * s);
}
