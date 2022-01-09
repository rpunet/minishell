/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:43:57 by jcarrete          #+#    #+#             */
/*   Updated: 2022/01/09 23:06:42 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	stream_literal(char *data, char **literal)
{
	char	*stack;
	char	*tmp;
	char	buff[2];

	buff[1] = '\0';
	stack = NULL;
	while (stack == NULL || ft_strlen(stack) - 1 != ft_strlen(data) || \
			ft_strncmp(data, stack, (int)ft_strlen(stack) - 1))
	{
		tmp = *literal;
		*literal = ft_strjoin(*literal, stack);
		tmp = ft_memfree(tmp, NULL);
		stack = ft_memfree(stack, NULL);
		buff[0] = 0;
		ft_dprintf(1, "> ");
		while (buff[0] != '\n')
		{
			read(0, buff, 1);
			tmp = stack;
			stack = ft_strjoin(stack, buff);
			tmp = ft_memfree(tmp, NULL);
		}
		printf("big buff is %s and strlen is %d\n", stack, (int)strlen(stack));
		printf("data is %s, and strlen is %d\n", data, (int)strlen(data));
		if (stack != NULL)
			printf("srtncmp is %d\n", ft_strncmp(data, stack, (int)ft_strlen(stack) - 1));
	}
	stack = ft_memfree(stack, NULL);
	printf("He salido");
}

int	here_doc(t_minishell *shell, t_exec *exec)
{
	pid_t	pid;
	char	*literal;

	literal = NULL;
	stream_literal(exec->cmd_node->data, &literal);
	if (pipe(exec->fds) == -1)
		exit_program(shell, F_SHELL, E_EXECUTE, strerror(errno));
	pid = fork();
	if (pid == -1)
		exit_program(shell, F_SHELL, E_EXECUTE, strerror(errno));
	else if (pid == 0)
	{
		close(exec->fds[P_IN]);
		ft_dprintf(exec->fds[P_OUT], literal);
		shell->std.in = exec->fds[P_IN];
		close(exec->fds[P_OUT]);
		literal = ft_memfree(literal, NULL);
		exit_program(shell, F_SUCCESS, E_NONE, NULL);
	}
	close(exec->fds[P_OUT]);
	literal = ft_memfree(literal, NULL);
	return (exec->fds[P_IN]);
}
