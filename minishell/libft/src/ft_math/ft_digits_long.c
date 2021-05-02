/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 13:08:58 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/18 13:53:48 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits_long(int nb)
{
	nb = ft_abs(nb);
	if (nb < 10)
		return (1);
	if (nb < 100)
		return (2);
	if (nb < 1000)
		return (3);
	if (nb < 10000)
		return (4);
	if (nb < 100000)
		return (5);
	if (nb < 1000000)
		return (6);
	if (nb < 10000000)
		return (7);
	if (nb < 100000000)
		return (8);
	if (nb <= INT_MAX)
		return (9);
	return (-1);
}
