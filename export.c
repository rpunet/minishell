#include "../libftPLUS/includes/libft.h"

int	main(int argc, char **argv, char **envp)
{
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return 0;
}
