/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/05/28 15:02:49 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtins[] = {
	"echo",
	"pwd",
	"cd"
};

int		(*ft_builtins[])(char **) = {
	&ft_echo,
	&ft_pwd,
	&ft_cd
};

int	double_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		ft_echo(char **args)
{
	int	i;

	if (!args[1])
		write(1, "\n", 1);
	else
	{
		//i = ft_strcmp(args[1], "-n") ? 1 : 2;		// como ponemos este ternario ?
		i = 1;
		if (!ft_strcmp(args[1], "-n"))
			i = 2;
		if ((i == 2 && args[2]) || i == 1)
		{
			while (args[i + 1])
			{
				ft_printf("%s ", args[i]);
				i++;
			}
			if (args[i])
				ft_printf("%s", args[i]);
			if (ft_strcmp(args[1], "-n"))
				write(1, "\n", 1);
		}
	}
	return (0);
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
		ft_printf("BUILTINpwd: too many arguments\n");  // revisar mensaje de error
	return (0);
}

int		ft_cd(char **args)
{
	if (chdir(args[1]) == -1)
		ft_printf("BUILTINcd: error\n");  // revisar mensaje de error
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
