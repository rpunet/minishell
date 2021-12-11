/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:23:57 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:48:32 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char c)
{
	int		i;
	char	*base;

	base = "0123456789abcdefABCDEF";
	i = ft_strchr_pos(base, c);
	return (i);
}

static int	s_value(char str)
{
	if (str == 45)
		return (-1);
	return (1);
}

static void	jump_prev(char *str, int *i, int *s)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		i++;
	*s = s_value(str[*i]);
	if (str[*i] == 45 || str[*i] == 43)
		i++;
}

int	ft_atoi_base(char *str, int base)
{
	int	s;
	int	i;
	int	pos;
	int	atoi;

	i = 0;
	atoi = 0;
	jump_prev(str, &i, &s);
	pos = check_base(str[i]);
	while (pos >= 0)
	{
		atoi *= base;
		if (ft_isdigit(str[i]))
			atoi += str[i] - 48;
		else if (str[i] >= 97 && str[i] <= 122)
			atoi += str[i] - 87;
		else if (str[i] >= 65 && str[i] <= 90)
			atoi += str[i] - 55;
		i++;
		pos = check_base(str[i]);
	}
	return (atoi * s);
}
