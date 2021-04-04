/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:54:34 by rpunet            #+#    #+#             */
/*   Updated: 2021/04/02 19:28:55 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	doublelen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_echo2(t_job *job, int j)
{
	int		i;
	char	**args;
	pid_t	pid;

	args = job->cmds[j].args;
	pid = fork();
	if (pid == 0)
	{
		if (job->cmds[j].io[WRITE] != -1)
			dup2(job->cmds[j].io[WRITE], STDOUT_FILENO);
		ft_close_fds(job);
		if (!args[1])
		{
			write(1, "\n", 1);
			exit(0);
		}
		if (ft_strcmp(args[1], "-n"))
			i = 1;
		else
			i = 2;
		while (args[i + 1])
		{
			ft_printf("%s ", args[i]);
			i++;
		}
		ft_printf("%s", args[i]);
		if (ft_strcmp(args[1], "-n"))
			write(1, "\n", 1);
		exit(0);
	}
}

void	ft_pwd2(t_job *job, int j)
{
	char	*ret;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (job->cmds[j].io[WRITE] != -1)
			dup2(job->cmds[j].io[WRITE], STDOUT_FILENO);
		ft_close_fds(job);
		if (doublelen(job->cmds[j].args) == 1)
		{
			ret = getcwd(NULL, 0);
			ft_printf("builtIN-%s\n", ret);
			free (ret);
			exit(0);
		}
		else
		{
			ft_printf("pwd: too many arguments\n");
			exit(0);
		}
	}
}

/* 	else if (pid < 0)
** 		gestion de error
** 	// else
** 	// 	while (waitpid(pid, NULL, 0) > 0);
*/

int	ft_cd(char **args)
{
	char	*ret;

	ret = args[1];
	if (chdir(ret) == -1)
		ft_printf("cd error");
	return (0);
}

int	ft_exit(char **args)
{
	if (args[0])
		exit(EXIT_SUCCESS);
	return (0);
}
