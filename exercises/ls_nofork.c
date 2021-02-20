#include <unistd.h>

int	main(void)
{
	execlp("/bin/ls", "ls", "-l", NULL);

	return 0;
}
