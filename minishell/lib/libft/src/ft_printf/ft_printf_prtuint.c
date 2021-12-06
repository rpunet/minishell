/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtuint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 11:58:16 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/11 22:30:27 by jcarrete         ###   ########.fr       */
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
			b->s = ft_utoa((unsigned long)temp);
		else
			b->s = ft_utoa(temp);
	}
	else
	{
		temp = va_arg(b->ap, unsigned int);
		if (b->flags.len_h)
			b->s = ft_utoa((unsigned short)temp);
		else if (b->flags.len_hh)
			b->s = ft_utoa((unsigned char)temp);
		else
			b->s = ft_utoa((unsigned int)temp);
	}
	ft_printf_prtdig(b);
}
