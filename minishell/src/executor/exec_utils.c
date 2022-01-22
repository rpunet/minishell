/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:43:34 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/22 23:23:07 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_redir(int type)
{
	if (type == REDIR_NODE || type == APPEND_NODE || \
		type == INDIR_NODE || type == LIMIT_NODE)
		return (TRUE);
	return (FALSE);
}

int	count_commands(t_ast_node *cmd_node)
{
	int			ret;
	t_ast_node	*curr;

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

char	*check_directories(DIR **dir, char **args, char **paths, int i)
{
	char			*path;
	struct dirent	*d;

	*dir = opendir(paths[i]);
	if (!*dir)
	{
		closedir(*dir);
		return (NULL);
	}
	errno = 0;
	d = readdir(*dir);
	while (*dir && errno == 0 && d)
	{
		if (!ft_strcmp(d->d_name, args[0]))
		{
			path = ft_strjoin(paths[i], "/");
			free_char_array(paths, double_len(paths));
			closedir(*dir);
			return (path);
		}
		d = readdir(*dir);
	}
	closedir(*dir);
	return (NULL);
}

char	*find_directory(DIR **dir, char **args)
{
	char	*path_var;
	char	**paths;
	char	*directory;
	int		i;

	if (!ft_strcmp(args[0], "minishell"))
		return (getenv("_"));
	path_var = getenv("PATH");
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		path_var = check_directories(dir, args, paths, i);
		if (path_var != NULL)
		{
			directory = ft_strjoin(path_var, args[0]);
			free(path_var);
			return (directory);
		}
		i++;
	}
	free_char_array(paths, double_len(paths));
	return (NULL);
}
