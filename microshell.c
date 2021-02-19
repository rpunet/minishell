#include <unistd.h>
#include <sys/wait.h>
#include "../libftPLUS/includes/libft.h"
#include <stdio.h>

#define READ	0
#define WRITE	1

int		n = 0; // numero de llamadas a comandos
char	**args;

int	execute(int input, int first, int last)
{
	int		fds[2];
	pid_t	pid;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		if (first == 1 && last == 0 && input == 0)	// primer comando
			dup2(fds[WRITE], STDOUT_FILENO);
		else if (first == 0 && last == 0 && input != 0)	// comandos intermedios
		{
			dup2(input, STDIN_FILENO);
			dup2(fds[WRITE], STDOUT_FILENO);
		}
		else if (first == 0 && last == 1)		// último comando
			dup2(input, STDIN_FILENO);
		if(execvp(args[0], args) == -1)			// ejecutar el nuevo proceso del comando
			exit(EXIT_FAILURE);
	}
	if (input != 0)
		close(input);
	close(fds[WRITE]);
	if (last == 1)
		close(fds[READ]);
	return (fds[READ]);
}

int	parse(char *cmd, int input, int first, int last)
{
	int		ret;

	ret = 0;
	args = ft_split(cmd, ' ');		// separar en comando (args[0] + argumentos (args[i])
	if (args[0] != NULL)
	{
		if (!ft_strcmp(args[0], "exit"))
			exit (0);
		n += 1;
		return (execute(input, first, last));
	}
	// faltaría liberar args
	return 0;
}

void	waitfor(int n)
{
	int	i = 0;

	while (i < n)
	{
		wait(NULL);
		++i;
	}
}

int	main()
{
	char	*line;
	char	*tok;
	int		input;	// retorno del comando previo, 0 si es el inicial
	int		first;	// 1 si es el primer comando de la secuencia de pipes
	int		last;	// 1 si es el último comando de la secuencia de pipes

	while (1)
	{
		ft_printf("microsh > ");
		if (get_next_line(0, &line) == -1)
			return 0;
		input = 0;
		first = 1;
		last = 0;
		tok = ft_strchr(line, '|');		//buscar el primer pipe
		while (tok != NULL)
		{
			*tok = '\0';
			input = parse(line, input, first, last);
			line = tok + 1;
			tok = ft_strchr(line, '|');		//buscar los siguientes pipes
			first = 0;
		}
		last = 1;
		parse(line, input, first, last);
		waitfor(n);
	}
	return 0;
}
