#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int	fd1[2], fd2[2];
	int	status, pid;

	pipe(fd1);

	pid = fork();
	if (pid == 0)
	{
		close(fd1[0]);
		dup2(fd1[1], 1);
		close(fd1[1]);
		execlp("/bin/ls", "ls", "-l", NULL);
	}
	close(fd1[1]);
	pipe(fd2);
	pid = fork();
	if (pid == 0)
	{
		close(fd2[0]);
		dup2(fd1[0], 0);
		close(fd1[0]);
		dup2(fd2[1], 1);
		close(fd2[1]);
		execlp("/bin/grep", "grep", "u", NULL);
	}
	close(fd1[0]);
	close(fd2[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd2[0], 0);
		close(fd2[0]);
		execlp("/usr/bin/wc", "wc", "-l", NULL);
	}
	close(fd2[0]);
	wait(&status);
	wait(&status);
	wait(&status);
	//perror("ls_3: ");
	return 0;
}
