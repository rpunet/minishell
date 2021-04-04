/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:08:12 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:41:44 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	mm_copy(size_t len, unsigned char *d, unsigned char *s, int i)
{
	while (len--)
	{
		d[i] = s[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned int	i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (dst == src || len == 0)
		return (dst);
	if (d < s)
		mm_copy(len, d, s, i);
	else
	{
		i = len - 1;
		while (len--)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (dst);
}
