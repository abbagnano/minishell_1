#include "my_minishell.h"

void	ft_env_line(char **line)
{
	char	*var;
	char	*tmp;
	int		x;
	int		len;

	x = 0;
	len = 0;
	tmp = *line;
	while (tmp[x] && tmp[x] != '$')
		x++;
	while (tmp[x + len] && tmp[x + len] != ' ')
		len++;
	var = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (tmp[x + len] != ' ')
	{
		var[len] = tmp[x + len];
		len++;
	}
	var[len] = '\0';
	printf("var: %s\n", var);

}