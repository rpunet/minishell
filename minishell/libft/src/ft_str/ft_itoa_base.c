/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:14:43 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 19:39:49 by jcarrete         ###   ########.fr       */
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

char	*ft_itoa_base(long long n, int base)
{
	char	*r;
	int		s;
	size_t	len;

	s = s_value(n);
	len = add_len(n, base);
	r = (char *)malloc(sizeof(char) * --len);
	if (r == NULL)
		return (NULL);
	r[len--] = '\0';
	while (n)
	{
		if (s * (n % base) < 10)
			r[len--] = s * (n % base) + 48;
		else
			r[len--] = s * (n % base) + 87;
		n = n / base;
	}
	if (s < 0)
		r[len] = '-';
	return (r);
}
