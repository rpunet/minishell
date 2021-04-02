/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtuint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 11:58:16 by jcarrete          #+#    #+#             */
/*   Updated: 2020/11/07 21:54:16 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_printf_prtuint(t_block *b)
{
	unsigned long long	temp;

	b->flags.f_plus = 0;
	b->flags.f_blank = 0;
	if (b->flags.f_minus || b->flags.pre >= 0)
		b->flags.f_zero = 0;
	if (b->flags.len_l || b->flags.len_ll)
	{
		temp = va_arg(b->ap, unsigned long long);
		if (b->flags.len_l)
			b->s = ft_ultoa((unsigned long)temp);
		else
			b->s = ft_ulltoa(temp);
	}
	else
	{
		temp = va_arg(b->ap, unsigned int);
		if (b->flags.len_h)
			b->s = ft_uitoa((unsigned short)temp);
		else if (b->flags.len_hh)
			b->s = ft_uitoa((unsigned char)temp);
		else
			b->s = ft_uitoa((unsigned int)temp);
	}
	ft_printf_prtdig(b);
}
