/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtwstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 13:51:13 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 21:44:17 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	putchar_var(t_block *b, char c)
{
	int	r;

	r = write(b->fd, &c, 1);
	return (r);
}

static void	encode_flag_wstr(t_block *b, wchar_t c, int *len)
{
	if (c <= 0x7F)
	{
		len -= putchar_var(b, c);
	}
	else if ((c >= 0x80 && c <= 0x7FF) && *len >= 2)
	{
		len -= putchar_var(b, (c >> 6) + 0xC0);
		len -= putchar_var(b, (c & 0x3F) + 0x80);
	}
	else if ((c >= 0x800 && c <= 0xFFFF) && *len >= 3)
	{
		len -= putchar_var(b, (c >> 12) + 0xE0);
		len -= putchar_var(b, ((c >> 6) & 0x3F) + 0x80);
		len -= putchar_var(b, (c & 0x3F) + 0x80);
	}
	else if ((c >= 0x10000 && c <= 0x10FFFF) && *len >= 4)
	{
		len -= putchar_var(b, (c >> 18) + 0xF0);
		len -= putchar_var(b, ((c >> 12) & 0x3F) + 0x80);
		len -= putchar_var(b, ((c >> 6) & 0x3F) + 0x80);
		len -= putchar_var(b, (c & 0x3F) + 0x80);
	}
}

static void	encode_wstr(t_block *b, wchar_t c)
{
	if (c <= 0x7F)
	{
		ft_putchar_fd(c, b->fd);
	}
	else if (c >= 0x80 && c <= 0x7FF)
	{
		ft_putchar_fd(((c >> 6) + 0xC0), b->fd);
		ft_putchar_fd(((c & 0x3F) + 0x80), b->fd);
	}
	else if (c >= 0x800 && c <= 0xFFFF)
	{
		ft_putchar_fd(((c >> 12) + 0xE0), b->fd);
		ft_putchar_fd((((c >> 6) & 0x3F) + 0x80), b->fd);
		ft_putchar_fd(((c & 0x3F) + 0x80), b->fd);
	}
	else if (c >= 0x10000 && c <= 0x10FFFF)
	{
		ft_putchar_fd(((c >> 18) + 0xF0), b->fd);
		ft_putchar_fd((((c >> 12) & 0x3F) + 0x80), b->fd);
		ft_putchar_fd((((c >> 6) & 0x3F) + 0x80), b->fd);
		ft_putchar_fd(((c & 0x3F) + 0x80), b->fd);
	}
}

static void	put_wstr(t_block *b, wchar_t *wstr, int *len)
{
	int	i;

	i = 0;
	while (wstr[i] && len)
	{
		if (b->flags.f_pad)
			encode_flag_wstr(b, wstr[i], len);
		else
		{
			encode_wstr(b, wstr[i]);
			len--;
		}
		i++;
		(b->ret)++;
	}
}

void	ft_printf_prtwstr(t_block *b, wchar_t *wstr)
{
	int	len;

	if (b->flags.pre < 0)
		len = ft_wstrlen(wstr);
	else
		len = b->flags.pre;
	if (b->flags.f_minus)
	{
		put_wstr(b, wstr, &len);
		ft_printf_prtwidth(b, len);
	}
	else
	{
		ft_printf_prtwidth(b, len);
		put_wstr(b, wstr, &len);
	}
	(b->i)++;
}
