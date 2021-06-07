/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:54:49 by jcarrete          #+#    #+#             */
/*   Updated: 2021/06/08 00:11:35 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_nothing(void *vd)
{
	(void)vd;
	return ;
}

void	free_char_array(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = ft_memfree(arr[i], NULL);
		i++;
	}
	arr = ft_memfree(arr, NULL);
}

void	*return_null(char *ptr)
{
	ptr = ft_memfree(ptr, NULL);
	return (NULL);
}

static void	failure_puttype(char *format, int *i, va_list *ap)
{
	char	*s1;

	if (format[*i] == 's')
	{
		s1 = va_arg(*ap, char *);
		if (s1 == NULL)
			ft_dprintf(STDERR_FILENO, "(null)");
		else
			ft_dprintf(STDERR_FILENO, s1);
		(*i)++;
	}
	else if (format[*i] == 'c')
	{
		ft_putchar_fd((char)va_arg(*ap, int), STDERR_FILENO);
		(*i)++;
	}
	else if (format[*i] == 'i')
	{
		s1 = ft_itoa((int)(va_arg(*ap, int)));
		ft_dprintf(STDERR_FILENO, s1);
		(*i)++;
	}
}

int	exit_failure(char *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	ft_dprintf(STDERR_FILENO, "ERROR:\n");
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			failure_puttype(format, &i, &ap);
		}
		else
			ft_putchar_fd(format[i++], STDERR_FILENO);
	}
	va_end(ap);
	exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
