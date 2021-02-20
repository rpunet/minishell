/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:50 by rpunet            #+#    #+#             */
/*   Updated: 2021/02/20 21:39:36 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../../libftPLUS/includes/libft.h"

# define READ		0
# define WRITE		1
# define BUILTINS	4

// STRUCTS   --------------------------------
typedef struct	s_cmd
{
	char	*name;
	int		io[2];
	char	**args;
}				t_cmd;

typedef struct	s_job
{
	int		n_cmds;
	int		n_pipes;
	int		(*fds)[2];
	t_cmd	*cmds;
}				t_job;

// BUILTINS ------------------------------
int		doublelen(char **arr);
int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_cd(char **args);
int		ft_exit(char **args);

// extern char	*builtins[];
// extern void	(*ft_builtins[])(char **);

void	ft_close_fds(t_job *job);
int		ft_execute(t_job *job);
void	ft_waitfor(int n);
t_job	*ft_parse(char *line);
int		ft_get_input(char **line);
void	ft_piping(t_job *job);
int		main(int argc, char **argv);

#endif
