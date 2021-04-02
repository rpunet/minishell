/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:22:02 by jcarrete          #+#    #+#             */
/*   Updated: 2020/12/12 23:49:17 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	str = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str[i] != str2[i] || str[i] == 0 || str2[i] == 0)
			return (str[i] - str2[i]);
		i++;
	}
	return (0);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*suffix;
	size_t			str_len;
	size_t			suffix_len;

	str = (unsigned char *)s1;
	suffix = (unsigned char *)s2;
	str_len = ft_strlen(s1);
	suffix_len = ft_strlen(s2);
	i = 1;
	if (str_len < suffix_len)
		return (-1);
	while (n--)
	{
		if (str[str_len - i] != suffix[suffix_len - i] ||\
			str[str_len - i] == 0 || suffix[suffix_len - i] == 0)
			return (str[str_len - i] - suffix[suffix_len - i]);
		i++;
	}
	return (0);
}
