/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:05:30 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:56:01 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_value(long double ld)
{
	if (ld < 0)
		return (-1);
	return (1);
}

char	*ft_ftoa(long double ld)
{
	char	*r;
	long	temp;
	int		len;
	int		s;

	s = s_value(ld);
	len = (ld < 0);
	ld *= s;
	temp = (long)ld;
	while (temp > 0 && len++ >= 0)
		temp /= 10;
	while (ld - (long)ld != 0 && len++ >= 0)
		ld *= 10;
	r = ft_strnew(len);
	while (--len >= 0)
	{
		r[len] = (long)ld % 10 + 48;
		ld /= 10;
		if (s == -1 && len == 1)
		{
			r[0] = '-';
			break ;
		}
	}
	return (r);
}
