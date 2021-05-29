#include "my_minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (s1 && s2 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	//printf("s1: %s\t s2: %s\t le: %d\n", s1, s2, len);
	while (s1 && s2 && *s1 && *s2 && *s1 == *s2 && --len)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strchr(char c, char *s1)
{
	int	x;

	x = 0;
	while (s1 && s1[x])
	{
		if (s1[x] == c)
			return (x);
		x++;
	}
	return (-1);
}

int		ft_strlen(char *str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_write(char *str)
{
	int len;

	len = ft_strlen(str);
	write(0, str, len);
}