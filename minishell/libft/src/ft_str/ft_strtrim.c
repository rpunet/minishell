/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:25:06 by jcarrete          #+#    #+#             */
/*   Updated: 2020/12/27 17:28:50 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(&s1[start]);
	if (end)
	{
		while (s1[start + end - 1] && ft_strchr(set, s1[start + end - 1]))
			end--;
	}
	return (ft_substr(s1, start, end));
}

char	*ft_strtrim_start(char const *s1, char const *set)
{
	size_t	start;
	int		set_long;
	char	*temp;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	set_long = ft_strlen(set);
	temp = ft_substr(s1, start, set_long);
	while (!(ft_strcmp(temp, (char *)set)))
	{
		start += set_long;
		temp = ft_memfree(temp, ft_substr(s1, start, set_long));
	}
	temp = ft_memfree(temp, NULL);
	return (ft_substr(s1, start, ft_strlen(s1)));
}
