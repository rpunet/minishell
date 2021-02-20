int	ft_execute(t_job *job)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < job->n_cmds)
	{
		pid = fork();
		if (pid == 0)
		{										//redirigir las i-o de los pipes.
			if (job->cmds[i].io[READ] != -1)
				dup2(job->cmds[i].io[READ], STDIN_FILENO);
			if (job->cmds[i].io[WRITE] != -1)
				dup2(job->cmds[i].io[WRITE], STDOUT_FILENO);
			i = 0;
			while (i < job->n_pipes)				// cerrar fds del hijo antiguos una vez copiados y redirigidos
			{
				close(job->fds[i][0]);
				close(job->fds[i][1]);
				i++;
			}
			return (execvp(job->cmds[i].name, job->cmds[i].args));
		}
		/*else
			// gestión de error del fork */
		i++;
	}
}
