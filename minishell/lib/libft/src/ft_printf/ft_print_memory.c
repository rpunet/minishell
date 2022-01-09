/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:25:57 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/09 18:36:03 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	hex_conv(unsigned char i)
{
	if (i <= 9)
		return ('0' + i);
	return ('a' - 10 + i);
}

static void	puthex(unsigned char c, int fd)
{
	unsigned char	p;
	unsigned char	s;

	p = hex_conv(c / 16);
	s = hex_conv(c % 16);
	ft_putchar_fd(p, fd);
	ft_putchar_fd(s, fd);
}

static void	putstr(char *str, size_t start, size_t len, int fd)
{
	size_t	i;

	i = 0;
	while ((start + i) < len && i < 16)
	{
		if (ft_isprint(str[i + start]))
			ft_putchar_fd(str[i + start], fd);
		else
			ft_putchar_fd('.', fd);
		i++;
	}
}

void	ft_print_memory(void *addr, size_t len, int fd)
{
	char	*str;
	size_t	l;
	size_t	i;

	str = addr;
	l = 0;
	while (l <= (len) / 16)
	{
		i = 0;
		while (i < 16)
		{
			if (i < len - (l * 16))
				puthex(str[i + (l * 16)], fd);
			else
				ft_putstr_fd("  ", fd);
			if (i % 4 == 3)
				ft_putchar_fd(' ', fd);
			i++;
		}
		putstr(str, l * 16, len, fd);
		ft_putchar_fd('\n', fd);
		l++;
	}
}
