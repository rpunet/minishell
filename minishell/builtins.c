/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/02/21 22:19:54 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		doublelen(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return i;
}

int		ft_echo(char **args)
{
	int i;

	if (!args[1])
	{
		write(1, "\n", 1);
		return 0;
	}
	i = ft_strcmp(args[1], "-n") ? 1 : 2;
	ft_printf("builtIN-%s: ", args[0]);
	while (args[i + 1])
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	ft_printf("%s", args[i]);
	if (ft_strcmp(args[1], "-n"))
		write(1, "\n", 1);
	return 0;
}

int		ft_pwd(char **args)
{
	char *ret;

	if (doublelen(args) == 1)
	{
		ret = getcwd(NULL, 0);
		ft_printf("builtIN-%s: ", args[0]);
		ft_printf("%s\n", ret);
		free (ret);
	}
	else
	{
		ft_printf("pwd: too many arguments\n");
	}
	return 0;
}

int		ft_cd(char **args)
{
	ft_printf("LLGA A DIR");
	char *ret;
	//ret = getcwd(NULL, 0);
	ret = args[1];
	if (chdir(ret) == -1)
		ft_printf("cd error");
	//perror("cd:");
	return 0;
}

int		ft_exit(char **args)
{
	ft_printf("builtIN-%s: ", args[0]);
	//if (pid != 0)
		exit(EXIT_SUCCESS);
}


