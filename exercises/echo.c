#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "../../libftPLUS/includes/libft.h"

int	main(int argc, char **argv)
{
	char	*line;
	char	**words;
	int		status;

	while (1){
		ft_printf("echosh %% ");
		get_next_line(0, &line);
		words = ft_split(line, ' ');
		if (fork() == 0)
		{
			if (!(strcmp(words[0], "echo")))
			{
				execlp("/bin/echo","echo", words[1], NULL);
			}
		}
		wait(&status);
	}
	return 0;
}
