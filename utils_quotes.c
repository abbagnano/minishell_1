#include "my_minishell.h"
#include "my_minishell2.h"

int	ft_cpy_matr(char **matr, char **new)
{
	int		y;
	char	**tmp;

	tmp = matr;
	y = 0;
	while (tmp && tmp[y])
	{
		new[y] = tmp[y];
		y++;
	}
	return (y);
}

void	ft_utils_quotes(int *a, int *z, char *str, char **new)
{
	if (str[*z + *a] == 39)
	{
		(*a)++;
		while (str[*z + *a] && str[*z + *a] != 39)
		{
			(*new)[*z] = str[*z + *a];
			(*z)++;
		}
		(*a)++;
	}
	else if (str[*z + *a] == 34)
	{
		(*a)++;
		while (str[*z + *a] && str[*z + *a] != 34)
		{
			(*new)[*z] = str[*z + *a];
			(*z)++;
		}
		(*a)++;
	}
}

int	ft_line_forward(char **line, int *z, int *x, char c)
{
	while ((*line)[*z] && (*line)[*z] != c)
		(*z)++;
	*x = *z;
	return (0);
}
