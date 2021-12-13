/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:03:12 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/13 23:38:55 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_prompt(char *sep)
{
	t_minishell	*shell;
	char		*ret;
	char		*tmp;

	shell = get_minishell(NULL);
	tmp = find_value(shell->envp_dup, "USER");
	ret = ft_strjoin(tmp, "@MINIsh ");
	tmp = ft_memfree(tmp, ft_strjoin(ret, "("));
	ret = ft_memfree(ret, ft_strjoin(tmp, ft_itoa(shell->exit_code)));
	tmp = ft_memfree(tmp, ft_strjoin(ret, ")"));
	ret = ft_memfree(ret, ft_strjoin(tmp, sep));
	return (ret);
}
