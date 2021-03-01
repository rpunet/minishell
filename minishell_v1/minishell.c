/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/02/27 22:31:17 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtins[] = {
//	"echo",
//	"pwd",
	"cd",
	"exit"
};

int		(*ft_builtins[])(char **) = {
//	&ft_echo,
//	&ft_pwd,
	&ft_cd,
	&ft_exit
};

void	ft_close_fds(t_job *job)
{
	int	i;

	i = 0;
	while (i < job->n_pipes)
	{
		close(job->fds[i][0]);
		close(job->fds[i][1]);
		i++;
	}
}


void	ft_waitfor(int n)
{
	int	i = 0;

	while (i < n)
	{
		wait(NULL);
		i++;
	}
	return ;
}


int	ft_get_input(char **line)
{
	ft_printf("newsh > ");
	if (get_next_line(0, line) == -1)
			return 1;
	return 0;
}

t_tok	*tok_init(int datasize)
{
	t_tok *token;

	if ((token = malloc(sizeof(t_tok))) == NULL)
		return (NULL);
	if ((token->data = malloc(datasize + 1)) == NULL)
		return (NULL);
	token->type = NULTOK;
	token->next = NULL;
	return (token);
}

int		char_type(char c)
{
	if (c )
}



int	main(int argc, char **argv)
{
	char	*line;
	t_lex	lexer;

	if (argc > 1 && !ft_strcmp(argv[1], "-c"))
		line = argv[2];
	while (1)
	{
		if (argc == 1)
			if (ft_get_input(&line))
				return 0;
		if (ft_lexer(line, &lexer, ft_strlen(line)))
			//error;


		if (argc > 1)			// esto es para que salga si la ejecucion es con -c
			break;
	}
	return 0;
}
