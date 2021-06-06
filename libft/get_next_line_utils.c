/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:27:55 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/30 02:15:10 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_newline(char **line, char *ptr, int r)
{
	int		i;
	int		y;
	char	*newline;
	int		tot;

	i = -1;
	y = 0;
	if (*line)
	{
		y = ft_strlen(*line);
		newline = (char *)malloc(sizeof(char) * (y + r + 1));
	}
	else
		newline = (char *)malloc(sizeof(char) * (r + 1));
	while (++i < y)
		newline[i] = line[0][i];
	i = 0;
	tot = r + y;
	while (y < tot)
		newline[y++] = ptr[i++];
	newline[y] = '\0';
	if (y > i)
		free(*line);
	return (newline);
}

int	ft_refresh_index(char **line, char *index)
{
	int	x;
	int	y;

	x = ft_strchr(index, '\n');
	y = ft_strlen(index);
	if (x == -1)
	{
		*line = ft_newline(line, index, y);
		ft_str_zero(index);
	}
	else
	{
		*line = ft_newline(line, index, x);
		ft_index(index, index, x + 1);
		return (1);
	}
	return (0);
}

void	ft_str_zero(char *ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		ptr[i++] = '\0';
}
