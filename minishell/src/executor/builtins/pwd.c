/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 15:47:59 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/12 15:48:24 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, char **envp)
{
	char	*ret;

	do_nothing(envp);
	if (double_len(args) == 1)
	{
		ret = getcwd(NULL, 0);
		ft_printf("%s\n", ret);
		free(ret);
	}
	else
		ft_printf("BUILTINpwd: too many arguments\n");
	return (EXIT_SUCCESS);
}
