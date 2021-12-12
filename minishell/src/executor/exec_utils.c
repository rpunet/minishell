/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:43:34 by jcarrete          #+#    #+#             */
/*   Updated: 2021/12/12 16:57:32 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_ast_node *cmd_node, t_ast_node *curr)
{
	int	ret;

	curr = cmd_node;
	ret = 0;
	while (curr != NULL && \
		(curr->type == CMDNAME_NODE || curr->type == TOKEN_NODE))
	{
		ret++;
		curr = curr->right;
	}
	return (ret);
}

int	exec_process(char **args, char **envp, int i)
{
	char	*directory;
	char	*path;
	DIR		*dir;

	directory = find_directory(&dir, args);
	if (!directory)
	{
		ft_printf("%s: Command not found\n", args[0]);
		free_char_array(args, i);
		exit_program(NULL, 0, 0, "");
	}
	path = ft_strjoin(directory, args[0]);
	return (execve(path, args, envp));
}

void	check_directories(DIR **dir, char **args, char **paths, int i)
{
	char			*path;
	struct dirent	*d;

	*dir = opendir(paths[i]);
	errno = 0;
	d = readdir(*dir);
	while (*dir && errno == 0 && d)
	{
		if (!ft_strcmp(d->d_name, args[0]))
		{
			path = ft_strjoin(paths[i], "/");
			free_char_array(paths, double_len(paths));
			return (path);
		}
		d = readdir(*dir);
	}
	closedir(*dir);
}

char	*find_directory(DIR **dir, char **args)
{
	char			*path_var;
	char			**paths;
	int				i;

	path_var = getenv("PATH");
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		check_directories(dir, args, paths, i);
		i++;
	}
	free_char_array(paths, double_len(paths));
	return (NULL);
}
