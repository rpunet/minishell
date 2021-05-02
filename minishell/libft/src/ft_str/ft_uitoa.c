/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 12:45:27 by jcarrete          #+#    #+#             */
/*   Updated: 2021/05/02 21:22:23 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	add_len(size_t n)
{
	size_t	len;

	len = 2;
	n = n / 10;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(size_t n)
{
	char	*r;
	size_t	len;

	len = add_len(n);
	r = (char *)malloc(sizeof(char) * len--);
	if (r == NULL)
		return (NULL);
	r[len--] = '\0';
	r[len--] = (n % 10) + 48;
	n = n / 10;
	while (n)
	{
		r[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (r);
}
