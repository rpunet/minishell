/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/05/28 12:51:55 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtins[] = {
	"pwd"
};

int		(*ft_builtins[])(char **) = {
	&ft_pwd
};

int	double_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		ft_pwd(char **args)
{
	char	*ret;

	if (double_len(args) == 1)
	{
		ret = getcwd(NULL, 0);
		ft_printf("builtIN-%s\n", ret);
		free(ret);
	}
	else
		ft_printf("BUILTINpwd: too many arguments\n");
	return (0);
}

int		check_builtins(char **args)
{
	int	i;

	i = 0;
	while ( i < BUILTINS)
	{
		if (!ft_strcmp(args[0], builtins[i]))
		{
			(*ft_builtins[i])(args);
			return (1);
		}
		i++;
	}
	return (0);
}





// int	ft_cd(char **args)
// {
// 	char	*ret;

// 	ret = args[1];
// 	if (chdir(ret) == -1)
// 		exit_failure("CD error\n");
// 	return (0);
// }

// int	ft_exit(char **args)
// {
// 	if (args[0])
// 		exit(EXIT_SUCCESS);
// 	return (0);
// }
