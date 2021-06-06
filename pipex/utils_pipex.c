#include "pipex.h"

int	ft_strchr(char c, char *s1)
{
	int x;

	x = 0;
	while (s1 && s1[x] && s1[x] != c)
		x++;
	if (!*s1)
		return (-1);
	return (x);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	while (s1 && s2 && *s1 && *s2 && *s1 == *s2 && len)
	{
		s1++;
		s2++;
		len--;
	}
	if (len)
		return (0);
	else
		return (1);
}

int	ft_strlen(char *s1)
{
	int x;

	x = 0;
	while (s1[x])
		x++;
	return (x);
}

void	ft_find_path_env(int *x, char **env)
{
	*x = 0;
	while (env && env[*x] && !ft_strncmp("PATH=", env[*x], 5))
		(*x)++;
}

void	ft_infile_to_sort(t_data *data, char *infile)
{
	int	x;

	x = 0;
	while (data->sort_av[x])
		x++;
	data->sort_av[x - 1] = infile;

}
