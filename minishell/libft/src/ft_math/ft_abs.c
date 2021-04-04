/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:03:49 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:34:49 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int a)
{
	if (a > 0 && a < INT_MIN)
		return (a);
	return (-a);
}

double	ft_absd(double a)
{
	if (a > 0)
		return (a);
	return (-a);
}

long double	ft_absld(long double a)
{
	if (a > 0)
		return (a);
	return (-a);
}
