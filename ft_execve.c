/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/02 10:07:24 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

void  ft_sign_ign_quit(int sig)
{
    //  char  c;

	printf("Quit: 3\n");
    // signal(sig, SIG_IGN);						//////		HO TOLTO QUESTO perche rimaneva in attesa di un segnale se si chiamava nuovamente cat

    //  printf("OUCH, did you hit Ctrl-C?\n"
    //         "Do you really want to quit? [y/n] \n");
    //  c = getchar();
    //  if (c == 'y' || c == 'Y')
    //       exit(0);
    //  else
    //       signal(SIGINT, INThandler);
    //  getchar(); // Get new line character
}

void	ft_sign_ign_int(int sig)
{
	printf("\n");
	// signal(sig, SIG_IGN);			//////		HO TOLTO QUESTO perche rimaneva in attesa di un segnale se si chiamava nuovamente cat
}

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
		ft_free_matrix(&data->args);
		signal(SIGQUIT, ft_sign_ign_quit);
		signal(SIGINT, ft_sign_ign_int);
		// signal(SIGQUIT, SIG_IGN);
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
	struct	stat fd_stat;
	
	// printf("loc_command\n");
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
	// exit(0);
	return (0);
}

int	ft_is_a_sys_com(t_data *data)
{
	char *path;
	int i;
	char **path_matrix;
	struct stat fd_stat;


	path = getenv("PATH");
	// printf("sys_command\n");
	path_matrix = ft_split(path, ':');
	// free(path);
	
	i  = -1;
	while (path_matrix[++i])
	{	
		// save = path_matrix[i];
		path = ft_strjoin(path_matrix[i], "/");
		// free(save);
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

int ft_check_execve(char *line, t_data *data)
{

	int r;
	struct stat fd_stat;

	r = 0;
	if (line)
		data->args = ft_split(line, ' ');
	if (ft_strchr('/', data->args[0]) == 0)   //TESTARE
	{
		// printf("abs_command\n");
		if (!stat(data->args[0], &fd_stat))
			r = 1;
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