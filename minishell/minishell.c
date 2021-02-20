/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:51:47 by rpunet            #+#    #+#             */
/*   Updated: 2021/02/20 21:39:34 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtins[] = {
	"echo",
	"pwd",
	"cd",
	"exit"
};

int		(*ft_builtins[])(char **) = {
	&ft_echo,
	&ft_pwd,
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

int	ft_execute(t_job *job)
{
	pid_t	pid;
	int		i;
	int		j;

	j = 0;
	while (j < job->n_cmds)
	{
		i = 0;
		while (i < BUILTINS)
		{
			if (!ft_strcmp(job->cmds[j].name, builtins[i]))
			{
				if (!job->n_pipes)
					return (*ft_builtins[i])(job->cmds[j].args);
				else
				{
					(*ft_builtins[i])(job->cmds[j].args);
				}
			}
			i++;
		}
		pid = fork();
		if (pid == 0)
		{										//redirigir las i-o de los pipes.
			if (job->cmds[j].io[READ] != -1)
				dup2(job->cmds[j].io[READ], STDIN_FILENO);
			if (job->cmds[j].io[WRITE] != -1)
				dup2(job->cmds[j].io[WRITE], STDOUT_FILENO);
			ft_close_fds(job);


			return (execvp(job->cmds[j].name, job->cmds[j].args));
		}
		/*else
			// gestión de error del fork */
		j++;
	}
}

void	ft_waitfor(int n)
{
	int	i = 0;

	while (i < n)
	{
		wait(NULL);
		++i;
	}
}

t_job	*ft_parse(char *line)
{
	t_job	*new;
	int		i;
	char	**cmds;
	char	**aux;

	cmds = ft_split(line, '|');
	aux = cmds;
	i = 0;
	while (*aux != NULL)
	{
		aux++;
		i++;
	}
	new = malloc(sizeof(t_job));
	new->n_cmds = i;
	new->cmds = malloc(sizeof(t_cmd) * new->n_cmds);
	i = 0;
	while (i < new->n_cmds)
	{
		new->cmds[i].args = ft_split(cmds[i], ' ');
		new->cmds[i].io[0] = -1;		//inicializar ios a -1 hasta que se creen los pipes;
		new->cmds[i].io[1] = -1;
		new->cmds[i].name = ft_strdup(new->cmds[i].args[0]);
		i++;
	}
	return (new);
}

int	ft_get_input(char **line)
{
	ft_printf("newsh > ");
	if (get_next_line(0, line) == -1)
			return 1;
	return 0;
}

void	ft_piping(t_job *job)
{
	int	i;

	job->n_pipes = job->n_cmds - 1;

	job->fds = malloc(sizeof(int[2]) * job->n_pipes);
	i = 0;
	while (i < job->n_pipes) // cada loop crea un pipe: el extremo izda. de entrada (escritura) se copia en el comando actual, y el de salida dcha.(lectura) como entrada para el siguiente comando. La entrada del primer comando y la salida del último quedan a -1.
	{
		pipe(job->fds[i]);
		job->cmds[i].io[STDOUT_FILENO] = job->fds[i][WRITE];
		job->cmds[i + 1].io[STDIN_FILENO] = job->fds[i][READ];
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*line;
	t_job	*job;

	int		i;

	if (argc > 1 && !ft_strcmp(argv[1], "-c"))
		line = argv[2];
	while (1)
	{
		if (argc == 1)
			if (ft_get_input(&line))
				return 0;
		job = ft_parse(line);
		ft_piping(job);
		if (ft_execute(job) == -1)
			perror("error");
		ft_close_fds(job);		// cerrar fds padre
		ft_waitfor(job->n_cmds);
		if (argc > 1)			// esto es para que salga si la ejecucion es con -c
			break;
	}
	return 0;
}
