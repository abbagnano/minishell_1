/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/06 17:06:18 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

void	ft_do_execve(char *line, t_data *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		ft_exit(strerror(errno), data);
	if (pid == 0)
	{
		execve(data->args[0], data->args, data->envp);
		ft_execve_failed(line, data);
	}
	else
	{
		ft_free_matrix(&data->args);
		g_pid = pid;
		signal(SIGQUIT, ft_sign_ign_quit);
		signal(SIGINT, ft_sign_ign_int);
		signal(SIGCHLD, ft_kill_child);
		waitpid(pid, &status, 0);
		if (!WIFSIGNALED(status))
			errno = status;
		pid = WEXITSTATUS(status);
		if (pid)
			errno = pid;
	}
}

int	ft_is_a_loc_com(t_data *data)
{
	char		*path;
	struct stat	fd_stat;

	path = getcwd(NULL, 0);
	ft_strjoin_over(&path, "/");
	ft_strjoin_over(&path, data->args[0]);
	if (!stat(path, &fd_stat))
	{
		free(data->args[0]);
		data->args[0] = ft_strdup(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	ft_is_a_sys_com(t_data *data)
{
	char		*path;
	int			i;
	char		**path_matrix;
	struct stat	fd_stat;

	path = getenv("PATH");
	path_matrix = ft_split(path, ':');
	i = -1;
	while (path_matrix[++i])
	{	
		path = ft_strjoin(path_matrix[i], "/");
		ft_strjoin_over(&path, data->args[0]);
		if (!stat(path, &fd_stat))
		{
			free(data->args[0]);
			data->args[0] = ft_strdup(path);
			free(path);
			ft_free_matrix(&path_matrix);
			return (1);
		}
		free(path);
	}
	ft_free_matrix(&path_matrix);
	return (0);
}

int	ft_check_execve(char *line, t_data *data)
{
	int			r;
	struct stat	fd_stat;

	r = 0;
	if (line)
		data->args = ft_split(line, ' ');
	if (ft_strchr('/', data->args[0]) == 0)
	{
		if (!stat(data->args[0], &fd_stat))
			r = 1;
		else
			r = 0;
	}
	else if (ft_strchr('.', data->args[0]) == 0)
	{
		if (ft_is_a_loc_com(data))
			r = 1;
	}
	else if (ft_is_a_sys_com(data))
		r = 1;
	if (r == 0)
		ft_free_matrix(&data->args);
	return (r);
}
