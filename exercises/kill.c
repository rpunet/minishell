#include "../../libftPLUS/includes/libft.h"
#include <unistd.h>
#include <signal.h>

void	mysighandler(int sig)
{
	ft_printf("signal number is %d \n", sig);
}

int	main(void)
{
	int *q = NULL;
	signal(SIGALRM, &mysighandler);
	while(1)
	{
		ft_printf(" %p \n", q);
		ft_printf("zzZZZZzzz\n");
		sleep(3);
	}
	return 0;
}
