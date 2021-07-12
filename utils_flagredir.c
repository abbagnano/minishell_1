/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flagredir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 01:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/12 10:23:51 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_flag_1(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_flag_2(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	ft_flag_3(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	ft_flag_4(char *file, t_data *data)
{
	int	fd;

	fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	write(data->std_fd[1], ">", 1);
	data->flag = 1;
	ft_flag4_reading(data, 0, fd, file);
	close(fd);
	tcsetattr(0, 0, &data->old_term);
	data->flag = 0;
	fd = open("/tmp/minishell", O_RDONLY, 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_flag_5(char *file)
{
	int	fd;

	fd = open(file, O_RDWR, 0666);
	if (fd < 0)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}
