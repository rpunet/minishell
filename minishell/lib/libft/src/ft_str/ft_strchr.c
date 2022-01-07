/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:15:25 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/07 13:13:37 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (char)c;
	i = 0;
	while (s[i] != c)
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

size_t	ft_strchr_count(const char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	ft_strchr_pos(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*r;

	c = (char)c;
	r = (char *)s;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (r[len] == c)
			return (&r[len]);
		len--;
	}
	if (r[len] == c)
		return (r);
	return (0);
}

int	ft_strrchr_pos(char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == c)
			return (len);
		len--;
	}
	return (-1);
}
