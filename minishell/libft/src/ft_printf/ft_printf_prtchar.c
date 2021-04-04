/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 12:41:10 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 21:59:03 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	print_str(t_block *b)
{
	char	*temp;
	int		len;

	len = (int)ft_strlen(b->s);
	if (b->flags.pre >= 0 && b->flags.pre < len)
	{
		temp = ft_substr(b->s, 0, (b->flags.pre));
		b->s = (char *)ft_memfree(b->s, temp);
		len = (int)ft_strlen(b->s);
	}
	if (b->flags.f_minus)
	{
		b->ret += write(b->fd, b->s, len);
		ft_printf_prtwidth(b, len);
	}
	else
	{
		ft_printf_prtwidth(b, len);
		b->ret += write(b->fd, b->s, len);
	}
	b->s = (char *)ft_memfree(b->s, NULL);
	(b->i)++;
}

static void	print_char(t_block *b, char c)
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

void	ft_printf_prtchar(t_block *b, char c)
{
	int		tempc;
	char	*temps;

	b->type = c;
	if (b->flags.f_minus)
		b->flags.f_zero = 0;
	if (b->type == 'c')
	{
		tempc = va_arg(b->ap, int);
		print_char(b, (char)tempc);
	}
	else if (b->type == 's')
	{
		temps = va_arg(b->ap, char *);
		if (temps == NULL)
			return (ft_printf_prtnull(b));
		b->s = ft_strdup((char *)temps);
		print_str(b);
	}
}
