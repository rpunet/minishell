/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:14:43 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 19:12:57 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	add_len(size_t n, int base)
{
	size_t	len;

	len = 1;
	while (n)
	{
		n = n / (unsigned)base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(size_t n, int base)
{
	char			*r;
	size_t			len;

	len = add_len(n, base);
	r = (char *)malloc(sizeof(char) * len--);
	if (r == NULL)
		return (NULL);
	r[len--] = '\0';
	while (n)
	{
		if ((n % base) < 10)
			r[len--] = (n % base) + 48;
		else
			r[len--] = (n % base) + 87;
		n = n / (unsigned)base;
	}
	return (r);
}
