/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtpoint.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:34:32 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/11 22:32:31 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_printf_prtaddr_width(t_block *b)
{
	int	len;

	len = ft_strlen(b->s);
	if (b->flags.f_minus)
	{
		b->ret += write(b->fd, b->s, len);
		while (b->flags.width > len)
		{
			b->ret += write(b->fd, " ", 1);
			(b->flags.width)--;
		}
	}
	else
	{
		while (b->flags.width > len)
		{
			b->ret += write(b->fd, " ", 1);
			(b->flags.width)--;
		}
		b->ret += write(b->fd, b->s, len);
	}
}

static void	ft_printf_prtaddr_pre(t_block *b)
{
	int		len;
	char	*temp;
	char	*r;

	len = ft_strlen(b->s);
	if (len < b->flags.pre)
	{
		temp = ft_strnew(b->flags.pre - len);
		ft_memset(temp, '0', (b->flags.pre - len));
		r = ft_strjoin(temp, b->s);
		b->s = ft_memfree(b->s, r);
		temp = ft_memfree(temp, NULL);
	}
	temp = ft_strjoin("0x", b->s);
	b->s = ft_memfree(b->s, temp);
	ft_str_tolower(b->s);
}

void	ft_printf_prtpoint(t_block *b)
{
	unsigned long	temp;
	unsigned long	addr;

	temp = (unsigned long)va_arg(b->ap, void *);
	addr = (unsigned long)temp;
	if (b->flags.pre == 0 && temp == 0)
		b->s = ft_strdup("\0");
	else
		b->s = ft_utoa_base(addr, 16);
	if (b->flags.f_zero && b->flags.pre < 0)
		b->flags.pre = b->flags.width - 2;
	else if (b->flags.pre == 0 && temp != 0)
		b->flags.pre = 1;
	ft_printf_prtaddr_pre(b);
	ft_printf_prtaddr_width(b);
	b->s = ft_memfree(b->s, NULL);
	(b->i)++;
}
