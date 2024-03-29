/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:10:55 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/06 20:59:07 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t len)
{
	unsigned char	*p;
	unsigned char	*q;
	unsigned char	temp;
	size_t			i;

	p = a;
	q = b;
	i = 0;
	while (i != len)
	{
		temp = p[i];
		p[i] = q[i];
		q[i] = temp;
		i++;
	}
}

void	ft_swap_int(int *p, int *q)
{
	int	t;

	t = *p;
	*p = *q;
	*q = t;
}

void	ft_swap_array_elem(void **array, int a, int b)
{
	void	*temp;

	temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

void	ft_swap_str(char **a, char **b)
{
	char	*t;

	if (!(*a) || !(*b))
		return ;
	t = *a;
	*a = *b;
	*b = t;
}
