/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:14:43 by jcarrete          #+#    #+#             */
/*   Updated: 2021/05/02 13:53:46 by jcarrete         ###   ########.fr       */
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

	len = 2;
	if (base == 10)
		len += (n < 0);
	n = n / base;
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static char	set_char(long long n, int base, int s)
{
	int	comp;

	comp = s * (n % base);
	if (comp < 10)
		return (s * (n % base) + 48);
	else
		return (s * (n % base) + 87);
}

char	*ft_itoa_base(long long n, int base)
{
	char	*r;
	int		s;
	size_t	len;

	s = s_value(n);
	len = add_len(n, base);
	r = (char *)malloc(sizeof(char) * len--);
	if (r == NULL)
		return (NULL);
	r[len--] = '\0';
	r[len--] = set_char(n, base, s);
	n = n / base;
	while (n)
	{
		r[len--] = set_char(n, base, s);
		n = n / base;
	}
	if (s < 0 && base == 10)
		r[len] = '-';
	return (r);
}
