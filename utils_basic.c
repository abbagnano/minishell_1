/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:22:55 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:22:56 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_write(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
}
