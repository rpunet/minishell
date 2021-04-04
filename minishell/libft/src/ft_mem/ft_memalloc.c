/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 17:02:04 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:38:04 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*all;

	all = malloc(size);
	if (all == NULL)
		return (0);
	ft_bzero(all, size);
	return (all);
}

void	*ft_memfree(void *all, void *npo)
{
	if (all)
		free(all);
	return (npo);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*r;

	r = (void *)malloc(count * size);
	if (r == NULL)
		return (NULL);
	ft_bzero(r, (count * size));
	return (r);
}

char	*ft_strnew(size_t size)
{
	return ((char *)ft_memalloc((sizeof(char) * (size + 1))));
}
