/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:22:08 by jcarrete          #+#    #+#             */
/*   Updated: 2021/02/07 23:50:45 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_qsort_min(char *a, char *b)
{
	if (a > b)
		return (b);
	return (a);
}

void	ft_qsort_push(t_qsort **top, char *low, char *high)
{
	(*top)->lo = low;
	(*top)->hi = high;
	(*top)++;
}

void	ft_qsort_pop(t_qsort **top, char *low, char *high)
{
	(*top)--;
	low = (*top)->lo;
	high = (*top)->hi;
	(void)low;
	(void)high;
}

void	ft_qsort_swap(char *a, char *b, size_t size)
{
	char	tmp;

	while (size > 0)
	{
		tmp = *a;
		*a++ = *b;
		*b++ = tmp;
		size--;
	}
}
