/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:19:13 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:19:15 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_check_quote(char	*line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'')
		{
			x++;
			while (line[x] && line[x] != '\'')
				x++;
			if (!line[x])
				return (0);
		}
		else if (line[x] == '\"')
		{
			x++;
			while (line[x] && line[x] != '\"')
				x++;
			if (!line[x])
				return (0);
		}		
		x++;
	}
	return (1);
}

void	ft_clean_clean(char **line, int e, int s)
{
	char	*new;
	int		x;
	int		y;

	new = (char *)malloc(sizeof(char) * (ft_strlen(*line) - 1));
	x = 0;
	y = 0;
	while ((*line)[x + y])
	{
		if (x + y == e || x + y == s)
			y++;
		if (!(*line)[x + y])
			break ;
		new[x] = (*line)[x + y];
		x++;
	}
	new[x] = '\0';
	free(*line);
	*line = new;
}

int	ft_check_clean(char **line, int *x, int s, char c)
{
	int	z;

	z = *x;
	s = z;
	while ((*line)[z])
	{
		z++;
		if ((*line)[z] && c == 39 && ((*line)[z] == '$' || (*line)[z] == '\"'))
			return (ft_line_forward(line, &z, x, c));
		else if ((*line)[z] && c == 34 && (*line)[z] == '\'')
			return (ft_line_forward(line, &z, x, c));
		else if ((*line)[z] && ((*line)[z] == '>'
			|| (*line)[z] == '<' || (*line)[z] == ' '))
			return (ft_line_forward(line, &z, x, c));
		else if ((*line)[z] && (*line)[z] == c)
		{
			*x = z - 2;
			ft_clean_clean(line, s, z);
			return (1);
		}
	}
	return (0);
}

void	ft_clean_quotes(char **line)
{
	int		x;

	x = 0;
	while ((*line)[x])
	{	
		if ((*line)[x] == 39)
			ft_check_clean(line, &x, 0, 39);
		else if ((*line)[x] == '\"')
			ft_check_clean(line, &x, 0, '\"');
		x++;
	}
}
