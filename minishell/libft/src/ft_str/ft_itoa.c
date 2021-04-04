/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:47:04 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 19:45:37 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_value(long long n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static size_t	add_len(long long n, int base)
{
	size_t	len;

	len = 1 + (n < 0);
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char	*ft_itoa(long long n)
{
	char	*r;
	int		s;
	size_t	len;

	s = s_value(n);
	len = add_len(n, 10);
	r = (char *)malloc(sizeof(char) * --len);
	if (r == NULL)
		return (NULL);
	r[len--] = '\0';
	while (n)
	{
		if (s * (n % 10) < 10)
			r[len--] = s * (n % 10) + 48;
		else
			r[len--] = s * (n % 10) + 87;
		n = n / 10;
	}
	if (s < 0)
		r[len] = '-';
	return (r);
}
