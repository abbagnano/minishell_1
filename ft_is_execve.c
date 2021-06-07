/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/07 10:19:01 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int ft_do_execve(t_data *data)
{
	int pid;
	int status;
	
	pid = fork();
	if (pid == 0)
	{
		execve(data->com_matrix[0], data->com_matrix, data->envp);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status)  && !WEXITSTATUS(status))
			return (1);			//SUCCESS
		else 
			return (0);			//NOT SUCCESS
	}
	return (0);
}

int ft_is_a_loc_com(t_data *data)
{
	char	*path;
	char	*save;
	int		fd;

	path = getcwd(NULL, 0);
	save = path;
	path = ft_strjoin(path, "/");
	free(save);	
	path = ft_strjoin(path, data->com_matrix[0]);
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		free(data->com_matrix[0]);
		data->com_matrix[0] = ft_strdup(path);
		free(path);
		close(fd);
		return (1);
	}
	free(path);
	return (0);
}

int	ft_is_a_sys_com(t_data *data)
{
	char *path;
	char *save;
	int fd;
	int i;
	char **path_matrix;

	path = getenv("PATH");
	path_matrix = ft_split(path, ':');
	
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
			free(data->com_matrix[0]);
			data->com_matrix[0] = ft_strdup(path);
			free(path);
			ft_free_matrix(&path_matrix);
			close(fd);
			return (1);
		}
		free(path);
	}
	ft_free_matrix(&path_matrix);
	return (0);
}

int ft_check_if_is_execve(char *line, t_data *data)
{

	int r;
	int fd;
	
	r = 0;
	data->com_matrix = ft_split(line, ' ');
	fd = open(data->com_matrix[0], O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		r = 1;
	}	
	else if (ft_strchr('.', data->com_matrix[0]) == 0)
	{
		if (ft_is_a_loc_com(data))
			r = 1;
		//ESEGUIRE IL LOCAL COMMAND COME ARGV[1] DI ./minishell     ?????
	}
	else if (ft_is_a_sys_com(data))
		r = 1;
	if (r == 0)
		ft_free_matrix(&data->com_matrix);
	return (r);
}