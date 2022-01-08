/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:48:52 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/08 15:43:16 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_arr_count(char **arr)
{
	int	ret;

	ret = 0;
	if (!arr)
		return (0);
	while (arr[ret] != NULL)
		ret++;
	return (ret);
}
