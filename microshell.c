#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../libftPLUS/includes/libft.h"


#define READ		0
#define WRITE		1
#define BUILTINS	3

int		n = 0; // numero de llamadas a comandos
char	**args;
char	*builtins[] = {
	"echo",
	"pwd",
	"cd"
};

void	ft_echo(char **args);
void	ft_pwd(char **args);
void	ft_cd(char **args);

void	(*ft_builtins[])(char **) = {
	&ft_echo,
	&ft_pwd,
	&ft_cd
};

int		doublelen(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return i;
}

void	ft_echo(char **args)
{
	int i;

	i = ft_strcmp(args[1], "-n") ? 1 : 2;
	for (i; args[i+1]; i++)
		ft_printf("%s ", args[i]);
	ft_printf("%s", args[i]);
	if (ft_strcmp(args[1], "-n"))
		write(1, "\n", 1);
}

void	ft_pwd(char **args)
{
	char *ret;

	if (doublelen(args) == 1)
	{
		ret = getcwd(NULL, 0);
		ft_printf("%s\n", ret);
		free (ret);
	}
	else
	{
		ft_printf("pwd: too many arguments\n");
	}
}

void	ft_cd(char **args)
{
	ft_printf("LLGA A DIR");
	if (chdir(args[1]) == -1)
		ft_printf("cd error");
	perror("cd:");
}

int	execute(int input, int first, int last)
{
	int		fds[2];
	pid_t	pid;
	int		i;

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
		i = 0;
		while (i < BUILTINS)
		{
			if (!ft_strcmp(args[0], builtins[i]))
			{
				(*ft_builtins[i])(args);
				exit(EXIT_SUCCESS);
			}
			i++;
		}
		if (execvp(args[0], args) == -1)			// ejecutar el nuevo proceso del comando
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

int	main(int argc, char **argv)
{
	char	*line;
	char	*tok;
	int		input;	// retorno del comando previo, 0 si es el inicial
	int		first;	// 1 si es el primer comando de la secuencia de pipes
	int		last;	// 1 si es el último comando de la secuencia de pipes

	if (argc > 1 && !ft_strcmp(argv[1], "-c"))
		line = argv[2];
	while (1)
	{
		if (argc == 1)
		{
			ft_printf("microsh > ");
			if (get_next_line(0, &line) == -1)
				return 0;
		}
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
		if (argc > 1)
			break;
	}
	return 0;
}
