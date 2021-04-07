/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:11:35 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/07 19:11:58 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_printf_conv_type_cont(const char *format, t_block *b)
{
	if (format[b->i] == 'n')
		ft_printf_prtret(b);
	else if (format[b->i] == 'f' || format[b->i] == 'g' || \
			format[b->i] == 'e' || format[b->i] == 'G' || format[b->i] == 'E')
		ft_printf_parseflt(b, format[b->i]);
	else if (format[b->i] == 'o')
		ft_printf_prtoct(b, format[b->i]);
	else if (format[b->i] != '\0')
		ft_printf_noprt(b, format[b->i]);
}

void	ft_printf_conv_type(const char *format, t_block *b)
{
	if (format[b->i] == '%')
		ft_printf_prtpct(b);
	else if (format[b->i] == 'c' || format[b->i] == 's')
	{
		if (b->flags.len_l == 0)
			ft_printf_prtchar(b, format[b->i]);
		else
			ft_printf_prtwchar(b, format[b->i]);
	}
	else if (format[b->i] == 'p')
		ft_printf_prtpoint(b);
	else if (format[b->i] == 'd' || format[b->i] == 'i')
		ft_printf_prtint(b);
	else if (format[b->i] == 'u')
		ft_printf_prtuint(b);
	else if (format[b->i] == 'x' || format[b->i] == 'X')
		ft_printf_prthex(b, format[b->i]);
	else
		ft_printf_conv_type_cont(format, b);
}
