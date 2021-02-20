#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../libftPLUS/includes/libft.h"

#define READ		0
#define WRITE		1
#define BUILTINS	4

// STRUCTS   --------------------------------
typedef struct s_cmd
{
	char	*name;
	int		io[2];
	char	**args;
}				t_cmd;

typedef struct s_job
{
	int		n_cmds;
	int		n_pipes;
	int		(*fds)[2];
	t_cmd	*cmds;
}				t_job;

// BUILTINS ------------------------------
char	*builtins[] = {
	"echo",
	"pwd",
	"cd",
	"exit"
};

void	ft_echo(char **args);
void	ft_pwd(char **args);
void	ft_cd(char **args);
void	ft_exit(char **args);

void	(*ft_builtins[])(char **) = {
	&ft_echo,
	&ft_pwd,
	&ft_cd,
	&ft_exit
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
	ft_printf("builtIN-%s: ", args[0]);
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
		ft_printf("builtIN-%s: ", args[0]);
		ft_printf("%s\n", ret);
		free (ret);
	}
	else
	{
		ft_printf("pwd: too many arguments\n");
	}
}

void	ft_cd(char **args)			// esto esta fallandoooo --------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx-----------------------
{
	ft_printf("LLGA A DIR");
	char *ret;
	//ret = getcwd(NULL, 0);
	ret = args[1];
	if (chdir(ret) == -1)
		ft_printf("cd error");
	perror("cd:");
}

void	ft_exit(char **args)
{
	ft_printf("builtIN-%s: ", args[0]);		// esto tampoco va, exit desde el hijo sale del hijo.
	//if (pid != 0)
		exit(EXIT_SUCCESS);
}


// MAIN ----------------------------------------------
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
		pid = fork();
		if (pid == 0)
		{										//redirigir las i-o de los pipes.
			if (job->cmds[j].io[READ] != -1)
				dup2(job->cmds[j].io[READ], STDIN_FILENO);
			if (job->cmds[j].io[WRITE] != -1)
				dup2(job->cmds[j].io[WRITE], STDOUT_FILENO);
			ft_close_fds(job);
			i = 0;
			while (i < BUILTINS)
			{
				if (!ft_strcmp(job->cmds[j].name, builtins[i]))
				{
					(*ft_builtins[i])(job->cmds[j].args);
					exit(EXIT_SUCCESS);
				}
				i++;
			}
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
