/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 23:08:25 by jcarrete          #+#    #+#             */
/*   Updated: 2021/02/10 18:56:13 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_up_pointers(t_qsort_data *data, t_qsort *tmp,\
						t_qsort **top, t_qsort *ptrs)
{
	if ((size_t)(ptrs->hi - tmp->lo) <= (4 * data->size))
	{
		if ((size_t)(tmp->hi - ptrs->lo) <= (4 * data->size))
			ft_qsort_pop(top, tmp->lo, tmp->hi);
		else
			tmp->lo = ptrs->lo;
	}
	else if ((size_t)(tmp->hi - ptrs->lo) <= (4 * data->size))
		tmp->hi = ptrs->hi;
	else if ((ptrs->hi - tmp->lo) > (tmp->hi - ptrs->lo))
	{
		ft_qsort_push(top, tmp->lo, ptrs->hi);
		tmp->lo = ptrs->lo;
	}
	else
	{
		ft_qsort_push(top, ptrs->lo, tmp->hi);
		tmp->hi = ptrs->hi;
	}
}

static void	collapse_the_walls(t_qsort_data *data, t_qsort *ptrs,\
								t_qsort *tmp, char *mid)
{
	ptrs->lo = tmp->lo + data->size;
	ptrs->hi = tmp->hi - data->size;
	while (ptrs->lo <= ptrs->hi)
	{
		while ((*(data->cmp))((void*)ptrs->lo, (void *)mid) < 0)
			ptrs->lo += data->size;
		while ((*(data->cmp))((void*)mid, (void *)ptrs->hi) < 0)
			ptrs->hi -= data->size;
		if (ptrs->lo < ptrs->hi)
		{
			ft_qsort_swap(ptrs->lo, ptrs->hi, data->size);
			if (mid == ptrs->lo)
				mid = ptrs->hi;
			else if (mid == ptrs->hi)
				mid = ptrs->lo;
			ptrs->lo += data->size;
			ptrs->hi -= data->size;
		}
		else if (ptrs->lo == ptrs->hi)
		{
			ptrs->lo += data->size;
			ptrs->hi -= data->size;
			break ;
		}
	}
}

static void	quicksort_partitions(t_qsort_data *data)
{
	t_qsort			tmp;
	t_qsort			stack[CHAR_BIT * sizeof(size_t)];
	t_qsort			*top;
	t_qsort			ptrs;
	char			*mid;

	tmp.lo = data->base_ptr;
	tmp.hi = &tmp.lo[data->size * (data->nmemb - 1)];
	top = stack;
	ft_qsort_push(&top, NULL, NULL);
	while (stack < top)
	{
		mid = tmp.lo + data->size * ((tmp.hi - tmp.lo) / data->size >> 1);
		if ((*(data->cmp))((void *)mid, (void *)tmp.lo) < 0)
			ft_qsort_swap(mid, tmp.lo, data->size);
		if ((*(data->cmp))((void *)tmp.hi, (void *)mid) < 0)
		{
			ft_qsort_swap(mid, tmp.hi, data->size);
			if ((*(data->cmp))((void *)mid, (void *)tmp.lo) < 0)
				ft_qsort_swap(mid, tmp.lo, data->size);
		}
		collapse_the_walls(data, &ptrs, &tmp, mid);
		set_up_pointers(data, &tmp, &top, &ptrs);
	}
}

void		ft_qsort_array(void *const base, size_t nmemb, size_t size,\
					t_compare cmp)
{
	t_qsort_data	data;

	data.base_ptr = (char *)base;
	data.nmemb = nmemb;
	data.size = size;
	data.cmp = cmp;
	if (nmemb < 1)
		return ;
	if (nmemb > 4)
		quicksort_partitions(&data);
	ft_insertion_sort(&data);
}
