/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 20:18:26 by jcarrete          #+#    #+#             */
/*   Updated: 2021/05/02 21:21:17 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	flag_pre(const char *format, t_block *b)
{
	if (b->flags.pre >= 0)
	{
		(b->i)++;
		return ;
	}
	if (format[b->i] == '.' && format[b->i + 1] == '*')
	{
		b->flags.pre = va_arg(b->ap, int);
		b->i += 2;
	}
	else if (format[b->i] == '.')
	{
		(b->i)++;
		b->flags.pre = ft_atoi(format + (b->i));
		while (ft_isdigit(format[b->i]))
			(b->i)++;
	}
}

static void	flag_len(const char *format, t_block *b)
{
	if (format[b->i] == 'h' && format[b->i + 1] != 'h')
		b->flags.len_h = 1;
	else if (format[b->i] == 'h' && format[b->i + 1] == 'h')
	{
		b->flags.len_hh = 1;
		(b->i)++;
	}
	else if (format[b->i] == 'l' && format[b->i + 1] != 'l')
		b->flags.len_l = 1;
	else if (format[b->i] == 'l' && format[b->i + 1] == 'l')
	{
		b->flags.len_ll = 1;
		(b->i)++;
	}
}

static void	flag_width(t_block *b)
{
	b->flags.width = va_arg(b->ap, int);
	if (b->flags.width < 0)
	{
		b->flags.width *= -1;
		b->flags.f_minus = 1;
	}
}

static void	basic_flags(const char *format, t_block *b)
{
	if (format[b->i] == '0')
		b->flags.f_zero = 1;
	else if (format[b->i] == '+')
		b->flags.f_plus = 1;
	else if (format[b->i] == '-')
		b->flags.f_minus = 1;
	else if (format[b->i] == '#')
		b->flags.f_pad = 1;
	else if (format[b->i] == ' ')
		b->flags.f_blank = 1;
}

void	ft_printf_conv_flag(const char *format, t_block *b)
{
	while (ft_strchr(PRINTF_FLAG, format[b->i]) && format[b->i] != '\0')
	{
		basic_flags(format, b);
		if (format[b->i] == '*')
			flag_width(b);
		if (format[b->i] == 'l' || format[b->i] == 'h')
			flag_len(format, b);
		if (format[b->i] == '.')
			flag_pre(format, b);
		else if ((format[b->i] >= 49 && format[b->i] <= 57) \
			&& b->flags.pre < 0)
		{
			b->flags.width = ft_atoi(format + (b->i));
			while (format[b->i] >= 48 && format[b->i] <= 57)
				(b->i)++;
		}
		else
			(b->i)++;
	}
}
