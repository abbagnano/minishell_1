/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/07 12:24:58 by arrigo           ###   ########.fr       */
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
		execve(data->args[0], data->args, data->envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)  && !WEXITSTATUS(status))
			return (0);			//SUCCESS
		else 
			return (1);			//NOT SUCCESS
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
	path = ft_strjoin(path, data->args[0]);
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		free(data->args[0]);
		data->args[0] = ft_strdup(path);
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
		path = ft_strjoin(path, data->args[0]);
		free(save);
		fd = open(path, O_RDONLY);
		if (fd > 0)
		{
			free(data->args[0]);
			data->args[0] = ft_strdup(path);
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
	data->args = ft_split(line, ' ');
	if (ft_strchr('/', data->args[0]) == 0)   //TESTARE
	{
		fd = open(data->args[0], O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			r = 1;
		}	
		else
			r = 0;
	}	
	else if (ft_strchr('.', data->args[0]) == 0)
	{
		if (ft_is_a_loc_com(data))
			r = 1;
		//ESEGUIRE IL LOCAL COMMAND COME ARGV[1] DI ./minishell     ?????
	}
	else if (ft_is_a_sys_com(data))
		r = 1;
	if (r == 0)
		ft_free_matrix(&data->args);
	return (r);
}