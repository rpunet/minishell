/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/02/20 21:16:55 by rpunet           ###   ########.fr       */
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

	i = ft_strcmp(args[1], "-n") ? 1 : 2;
	ft_printf("builtIN-%s: ", args[0]);
	for (i; args[i+1]; i++)
		ft_printf("%s ", args[i]);
	ft_printf("%s", args[i]);
	if (ft_strcmp(args[1], "-n"))
		write(1, "\n", 1);
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
}

int		ft_exit(char **args)
{
	ft_printf("builtIN-%s: ", args[0]);
	//if (pid != 0)
		exit(EXIT_SUCCESS);
}


