/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:43:34 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/12 21:04:46 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	run_executable(char **args, char **envp)
{
	int		find;
	char	*cwd;
	char	*path;
	char	*tmp;

	find = ft_strrchr_pos(args[0], '/');
	tmp = getcwd(NULL, 0);
	cwd = ft_strjoin(tmp, "/");
	path = ft_strjoin(cwd, args[0]);
	cwd = ft_memfree(cwd, NULL);
	tmp = ft_memfree(tmp, NULL);
	args[0] = args[0] + find + 1;
	if (access(path, F_OK) == 0)
		return (execve(path, args, envp));
	path = ft_memfree(path, NULL);
	args[0] = args[0] - find - 1;
	return (EXIT_SUCCESS);
}

int	exec_process(char **args, char **envp, int i)
{
	char		*directory;
	DIR			*dir;
	t_minishell	*shell;

	shell = get_minishell(NULL);
	directory = find_directory(&dir, args);
	if (!directory)
	{
		if (ft_iteris(args[0], &ft_isspace))
		{
			shell->exit_code = EXIT_SUCCESS;
			return (EXIT_SUCCESS);
		}
		if (run_executable(args, envp) == -1)
			return (EXEC_FAILURE);
		if (!ft_strcmp(args[0], "$?"))
			ft_dprintf(STDERR_FILENO, "%d", shell->exit_code);
		ft_dprintf(STDERR_FILENO, "%s: Command not found\n", args[0]);
		shell->exit_code = EB_COMMAND_NOT_FOUND;
		free_char_array(args, i);
		exit_program(NULL, 0, 0, "");
	}
	return (execve(directory, args, envp));
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
