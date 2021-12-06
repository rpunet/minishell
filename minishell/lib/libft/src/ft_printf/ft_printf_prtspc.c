/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtspc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 23:01:21 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 21:46:28 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_printf_noprt(t_block *b, char c)
{
	if (b->flags.f_minus)
	{
		b->ret += write(b->fd, &c, 1);
		ft_printf_prtwidth(b, 1);
	}
	else
	{
		ft_printf_prtwidth(b, 1);
		b->ret += write(b->fd, &c, 1);
	}
	(b->i)++;
}

void	ft_printf_prtnull(t_block *b)
{
	int	len;

	if (b->type == 'c')
	{
		if (b->flags.f_minus)
			b->ret += write(b->fd, "\0", 1);
		ft_printf_prtwidth(b, 1);
		if (!(b->flags.f_minus))
			b->ret += write(b->fd, "\0", 1);
		(b->i)++;
	}
	else if (b->type == 's')
	{
		if ((b->flags.pre < 0) || (b->flags.pre > 6))
			len = 6;
		else
			len = b->flags.pre;
		if (b->flags.f_minus)
			b->ret += write(b->fd, "(null)", len);
		ft_printf_prtwidth(b, len);
		if (!(b->flags.f_minus))
			b->ret += write(b->fd, "(null)", len);
		(b->i)++;
	}
}

void	ft_printf_prtpct(t_block *b)
{
	if (b->flags.f_minus)
	{
		b->flags.f_zero = 0;
		b->ret += write(b->fd, "%", 1);
	}
	ft_printf_prtwidth(b, 1);
	if (!(b->flags.f_minus))
		b->ret += write(b->fd, "%", 1);
	(b->i)++;
}
