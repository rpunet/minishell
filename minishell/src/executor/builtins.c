/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/11/27 20:40:42 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtins[] = {
	"echo",
	"pwd"
	// "cd"
	// "export",
	// "exit"
};

int		(*ft_builtins[])(char **, char **) = {
	&ft_echo,
	&ft_pwd
	// &ft_cd
	// &ft_export,
	// &ft_exit
};

int	double_len(char **arr)
{
	int	i;

	i = 0;
	if (!*arr || !arr)
		return 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_echo(char **args, char **envp)
{
	int	i;

	do_nothing(envp);
	if (!args[1])
		write(1, "\n", 1);
	else
	{
		i = 1;
		if (!ft_strcmp(args[1], "-n"))
			i++;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(args[1], "-n"))
			write(1, "\n", 1);
	}
	return (0);
}

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
		ft_printf("BUILTINpwd: too many arguments\n");  // revisar mensaje de error
	return (0);
}

int		ft_cd(char **args, char ***envp)
{
	char	*find;
	char	*save;
	char	*dir;


	if (double_len(args) <= 2)
	{													//AÑADIR EL cd ()(HOME)
		if (chdir(args[1]) == -1)
			ft_printf("BUILTINcd: No such file or directory\n");  // revisar mensaje de error
		else
		{
			save = find_value(*envp, "PWD");
			delete_var(envp, find = find_variable(*envp, "OLDPWD", NULL));
			free (find);
			dir = ft_strjoin("OLDPWD=", save);
			free(save);
			add_single_exp(envp, dir);
			free(dir);
			save = getcwd(NULL, 0);
			delete_var(envp, find = find_variable(*envp, "PWD", NULL));
			free (find);
			dir = ft_strjoin("PWD=", save);
			free(save);
			add_single_exp(envp, dir);
			free(dir);


			// add_single_exp(&envp, ft_strdup("PWD=0000"));
			// delete_var(&envp, ft_strdup("OLDPWD"));
		}
	//ft_printf("builtIN-cd\n");
	}
	else
		ft_printf("BUILTINcd: too many arguments\n");  // revisar mensaje de error
	return (0);
}

int		ft_exit(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}


int		check_builtins(char **args, char **envp)
{
	int	i;

	i = 0;
	if (!ft_strcmp(args[0], "env"))		// pasamos envp a todas para usar la función-tipo del puntero?
	{
		while (*envp)
		{
			ft_printf("%s\n", *envp);
			envp++;
		}
		return (1);
	}
	while ( i < BUILTINS)
	{
		if (!ft_strcmp(args[0], builtins[i]))
		{
			(*ft_builtins[i])(args, envp);
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

