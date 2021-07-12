/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/12 10:24:25 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

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

void	ft_quottes(char *line, int *i, int *c, int *x)
{
	char	q;

	q = line[*i];
	(*i)++;
	*c = *i;
	while (line[*c] && line[*c] != q)
		(*c)++;
	*x = *c + 1;
}

void	ft_slide_quotes(char *line, int *i)
{
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
	}	
}
