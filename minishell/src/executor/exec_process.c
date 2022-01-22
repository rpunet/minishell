/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:19:53 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/17 00:14:11 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_command_path(t_exec *exec)
{
	char	*ret;
	DIR		*dir;

	if (ft_strchr(exec->args[0], '/') == NULL)
		ret = find_directory(&dir, exec->args);
	else
	{
		ret = ft_strdup(exec->args[0]);
		if (access(ret, X_OK) != 0)
			ret = ft_memfree(ret, NULL);
	}
	return (ret);
}

int	exec_process(char **args, char **envp, int i)
{
	t_minishell	*shell;

	shell = get_minishell(NULL);
	if (shell->path == NULL)
	{
		if (ft_iteris(args[0], &ft_isspace))
		{
			shell->exit_code = EXIT_SUCCESS;
			return (EXIT_SUCCESS);
		}
		if (!ft_strcmp(args[0], "$?"))
			ft_dprintf(STDERR_FILENO, "%d", shell->exit_code);
		ft_dprintf(STDERR_FILENO, "%s: Command not found\n", args[0]);
		shell->exit_code = EB_COMMAND_NOT_FOUND;
		free_char_array(args, i);
		exit_program(NULL, 0, 0, "");
	}
	return (execve(shell->path, args, envp));
}
