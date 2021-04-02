/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort_insertion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:30:34 by jcarrete          #+#    #+#             */
/*   Updated: 2021/02/07 16:37:14 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	run_insertion_sort(t_qsort_data *data, char *run_ptr, char *tmp_ptr)
{
	char			*lo;
	char			*hi;
	char			*trav;
	char			c;

	tmp_ptr = run_ptr - data->size;
	while ((*data->cmp)((void *)run_ptr, (void *)tmp_ptr) < 0)
		tmp_ptr -= data->size;
	tmp_ptr += data->size;
	if (tmp_ptr != run_ptr)
	{
		trav = run_ptr + data->size;
		while (--trav >= run_ptr)
		{
			c = *trav;
			hi = trav;
			lo = trav;
			while ((lo -= data->size) >= tmp_ptr)
			{
				*hi = *lo;
				hi = lo;
			}
			*hi = c;
		}
	}
}

void		ft_insertion_sort(t_qsort_data *data)
{
	char *const		end_ptr = &(data->base_ptr)[data->size * (data->nmemb - 1)];
	char			*tmp_ptr;
	char			*thresh;
	register char	*run_ptr;

	tmp_ptr = data->base_ptr;
	thresh = ft_qsort_min(end_ptr, data->base_ptr + (4 * data->size));
	run_ptr = tmp_ptr + data->size;
	while (run_ptr <= thresh)
	{
		if ((*(data->cmp))((void *)run_ptr, (void *)tmp_ptr) < 0)
			tmp_ptr = run_ptr;
		run_ptr += data->size;
	}
	if (tmp_ptr != data->base_ptr)
		ft_qsort_swap(tmp_ptr, data->base_ptr, data->size);
	run_ptr = data->base_ptr + data->size;
	while ((run_ptr += data->size) <= end_ptr)
		run_insertion_sort(data, run_ptr, tmp_ptr);
}
