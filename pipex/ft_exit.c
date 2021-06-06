#include "pipex.h"

void	ft_exit(char *s, t_data *data)
{
	write(1, s, ft_strlen(s));
	printf("waiting_leaks\n");
	read(0, &s, 1);
	exit(0);
}