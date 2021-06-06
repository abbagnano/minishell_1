/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/06 17:26:37 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int	ft_free_matrix(char ***matrix)
{
	int	i;

	i = -1;
	if (!(*matrix))
		return (0);
	while ((*matrix)[++i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
	}
	free(*matrix);
	*matrix = NULL;
	return (0);
}


int	ft_path(char **path_matrix, t_data *data)
{
	char *path;
	char *save;
	int fd;
	int i;
	
	i  = -1;
	while (path_matrix[++i])
	{	
		path = ft_strjoin(path_matrix[i], "/");
		save = path;
		path = ft_strjoin(path, data->com_matrix[0]);
		free(save);
		fd = open(path, O_RDONLY);
		if (fd > 0)
		{
			data->path = path;
			close(fd);
			return (1);
		}
		free(path);
	}
	return (0);
}

int ft_check_if_is_execve(char *line, t_data *data)
{
	char *path;
	char **path_matrix;
	int i;
	int r;
	
	r = 0;
	i = -1;
	path = getenv("PATH");
	path_matrix = ft_split(path, ':');
	//	free(path);////////////////////////////////////free del ritorno di getenv?
	data->com_matrix = ft_split(line, ' ');
	r = ft_path(path_matrix, data);
	ft_free_matrix(&path_matrix);
	if (r == 0)
		ft_free_matrix(&data->com_matrix);
	return (r);
}