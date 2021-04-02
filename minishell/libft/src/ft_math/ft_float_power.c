/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_power.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:18:12 by jcarrete          #+#    #+#             */
/*   Updated: 2020/11/07 19:55:07 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_float_power(int nb, int base)
{
	int		temp;
	int		i;
	double	pre;

	temp = nb;
	pre = 1;
	i = 0;
	if (temp < 0)
	{
		temp *= -1;
		while (i < temp)
		{
			pre = pre / base;
			i++;
		}
	}
	else if (temp > 0)
		while (i < temp)
		{
			pre = pre * base;
			i++;
		}
	return (pre);
}
