/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prtoctal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 11:54:59 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 21:46:47 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_printf_flagpad_addzero(t_block *b, unsigned long long ul)
{
	char	*temp;

	if (b->flags.f_pad && b->s[0] != '0')
	{
		temp = ft_strappstart_nchr(b->s, '0', 1);
		b->s = ft_memfree(b->s, temp);
	}
	ft_printf_prtbase(b, (long)ul);
}

void	ft_printf_prtoct(t_block *b, char c)
{
	unsigned long long	temp;
	unsigned long long	ul;

	b->type = c;
	if (b->flags.len_l || b->flags.len_ll)
	{
		temp = va_arg(b->ap, unsigned long long);
		if (b->flags.len_l)
			ul = (unsigned long)temp;
		else
			ul = temp;
	}
	else
	{
		temp = va_arg(b->ap, unsigned int);
		if (b->flags.len_h)
			ul = (unsigned short)temp;
		else if (b->flags.len_hh)
			ul = (unsigned char)temp;
		else
			ul = (unsigned int)temp;
	}
	b->s = ft_ultoa_base(ul, 8);
	ft_printf_basepre(b);
	ft_printf_flagpad_addzero(b, ul);
}