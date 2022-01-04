/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:43:34 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/04 20:53:59 by rpunet           ###   ########.fr       */
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

// si la quieres meter en LIBFT, y por cierto tu strrchr esta mal (len >= 0)

int	ft_strrchr_pos(char *str, int c)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == c)
			return (len);
		len--;
	}
	return (-1);
}

int	run_executable(char **args, char **envp)
{
	int		find;
	char	*cwd;
	char	*path;

	// ft_printf("%s\n", cwd);
	find = ft_strrchr_pos(args[0], '/');
	cwd = ft_strjoin(getcwd(NULL, 0), "/");
	path = ft_strjoin(cwd, args[0]);
	//free(cwd);
	args[0] = args[0] + find + 1;		// esto provoca un free() invalid pointer si es command not found, habrá que usar un duplicado de args
	ft_printf("%i\n%s\n%s\n%s\n", find, path, args[0], args[1]);
	return (execve(path, args, envp));
	// si execve falla y retorna -1, como diferenciar error de execve, de command not found?
}


int	exec_process(char **args, char **envp, int i)
{
	char	*directory;
	char	*path;
	DIR		*dir;

	directory = find_directory(&dir, args);
	if (!directory)
	{
		run_executable(args, envp);
		ft_printf("%s: Command not found\n", args[0]);
		free_char_array(args, i);
		exit_program(NULL, 0, 0, "");
	}
	path = ft_strjoin(directory, args[0]);
	ft_printf("%s\n%s\n%s\n", path, args[0], args[1]);
	return (execve(path, args, envp));   // si execve falla, retorna -1
}

char	*check_directories(DIR **dir, char **args, char **paths, int i)
{
	char			*path;
	struct dirent	*d;

	*dir = opendir(paths[i]);
	if (!*dir)
	{
		closedir(*dir); // no se si hace falta cerrarlo o si es el open es erróneo y da NULL ya vale
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
	char			*path_var;
	char			**paths;
	int				i;

	path_var = getenv("PATH");
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		path_var = check_directories(dir, args, paths, i);
		if (path_var != NULL)
			return (path_var);
		i++;
	}
	free_char_array(paths, double_len(paths));
	return (NULL);
}
