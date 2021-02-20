/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:04:48 by rpunet            #+#    #+#             */
/*   Updated: 2021/01/28 11:43:17 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


#define	READ_END	0
#define	WRITE_END	1

int	main(int argc, char **argv)
{
	int	fd1[2], fd2;
	int	status, pid;

	pipe(fd1);

	pid = fork();

	if (pid == 0)
	{
		close(fd1[READ_END]);

		dup2(fd1[WRITE_END], STDOUT_FILENO);
		close(fd1[WRITE_END]);

		execlp("/bin/ls", "ls", "-l", NULL);
	}
	else
	{
		close(fd1[WRITE_END]);

		pid = fork();

		if (pid == 0)
		{
			fd2 = open("file_ls.txt", O_WRONLY | O_CREAT, 00600);
			dup2(fd1[READ_END], STDIN_FILENO);
			close(fd1[READ_END]);

			dup2(fd2, STDOUT_FILENO);
			close(fd2);
			execlp("/usr/bin/wc", "wc", NULL);
		}
		else
		{
			close(fd1[READ_END]);
		}
	}
	wait(&status);
	wait(&status);

	return 0;
}
