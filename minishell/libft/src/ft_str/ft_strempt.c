/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strempt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:55:25 by jcarrete          #+#    #+#             */
/*   Updated: 2020/11/07 19:59:41 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strempt(char *s)
{
	ft_bzero(s, ft_strlen(s));
}

void	ft_strempt_endchar(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == c)
		str[i--] = '\0';
}
