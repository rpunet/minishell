/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 23:14:43 by jcarrete          #+#    #+#             */
/*   Updated: 2021/05/02 21:22:19 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	add_len(size_t n, int base)
{
	size_t	len;

	len = 2;
	n = n / (unsigned)base;
	while (n)
	{
		n = n / (unsigned)base;
		len++;
	}
	return (len);
}

static char	set_char(size_t n, int base)
{
	int	comp;

	comp = (n % base);
	if (comp < 10)
		return ((n % base) + 48);
	else
		return ((n % base) + 87);
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
	r[len--] = set_char(n, base);
	n = n / (unsigned)base;
	while (n)
	{
		r[len--] = set_char(n, base);
		n = n / (unsigned)base;
	}
	return (r);
}
