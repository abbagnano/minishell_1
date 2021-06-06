/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:27:58 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/30 02:19:51 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	get_next_line(int fd, char **line)
{
	static char	index[BUFFER_SIZE + 1];
	int			x;

	x = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (index[0] != '\0')
		x = ft_refresh_index(line, index);
	if (x == 1)
		return (1);
	ft_str_zero(index);
	while (x == 0)
		x = ft_read_buff(fd, line, index);
	if (x == -2)
	{
		if (!*line)
		{
			*line = (char *)malloc(sizeof(char));
			line[0][0] = '\0';
		}
		x = 0;
	}
	return (x);
}

void	ft_index(char *index, char *ptr, int x)
{
	int	i;

	i = 0;
	while (ptr[x])
		index[i++] = ptr[x++];
	while (index[i])
		index[i++] = '\0';
}

int	ft_read_buff(int fd, char **line, char *index)
{
	int		r;
	int		x;
	char	ptr[BUFFER_SIZE + 1];

	r = 1;
	while (r)
	{
		r = read(fd, ptr, BUFFER_SIZE);
		if (r == -1)
			return (-1);
		ptr[r] = '\0';
		if (r == 0)
			return (-2);
		x = ft_strchr(ptr, '\n');
		if (x == -1)
		{
			*line = ft_newline(line, ptr, r);
			ft_str_zero(ptr);
			return (0);
		}
		*line = ft_newline(line, ptr, x);
		ft_index(index, ptr, x + 1);
		break ;
	}
	return (1);
}
