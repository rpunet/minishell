/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_exp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:18:50 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/07 19:26:45 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_printf_create_exponent(int e)
{
	char	*temp1;

	if (e < -9)
		temp1 = ft_strjoin("e", "-");
	else if (e < 0 && e >= -9)
		temp1 = ft_strjoin("e", "-0");
	else if (e > 9)
		temp1 = ft_strjoin("e", "+");
	else
		temp1 = ft_strjoin("e", "+0");
	return (temp1);
}
