/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:17:10 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 16:00:40 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_duplicate(char const *s1, char const *s2)
{
	if (!(s1))
		return (ft_strdup(s2));
	return (ft_strdup(s1));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (return_duplicate(s1, s2));
	str = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1len + 1);
	ft_strlcat(str + s1len, s2, s2len + 1);
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*str;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (return_duplicate(s1, s2));
	str = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1len + 1);
	ft_memfree(s1, NULL);
	ft_strlcat(str + s1len, s2, s2len + 1);
	return (str);
}
