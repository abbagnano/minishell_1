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

int g_g;

void  ft_sign_ign_quit(int sig)
{
    //  char  c;

	printf("Quit: 3   %d\n", sig);
	ft_write("Quit: 3\n");
	errno = 128 + sig;
    // signal(sig, SIG_IGN);						//////		HO TOLTO QUESTO perche rimaneva in attesa di un segnale se si chiamava nuovamente cat
	// kill(g_g, SIGTERM);
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
	// printf("\n");
	ft_write("\n");
	errno = 128 + sig;
	// kill(g_g, SIGTERM);
	// signal(sig, SIG_IGN);			//////		HO TOLTO QUESTO perche rimaneva in attesa di un segnale se si chiamava nuovamente cat
}
void	ft_kill_child(int sig)
{
	// printf("sig: %d\n", sig);
	// printf("sdfsdfsdfdsfsdfsdfsdfsdfsdfgsd\n");
	// g_g++;
	kill(g_g, SIGTERM);
}

int ft_do_execve(char *line, t_data *data)
{
	int pid;
	int status;
	
	pid = fork();
	if (pid == 0)
	{
		int ret;
		ret = execve(data->args[0], data->args, data->envp);
		printf("ret:%d\n", ret);
		dup2(data->std_fd[1],1);
		dup2(data->std_fd[0], 0);
		ft_write_2(strerror(errno));
		ft_free_matrix(&data->args);
		free(line);
		// char *asd = strerror(errno);
		// write(2, asd, strlen(asd));
		// perror(data->args[0]);
		// ft_write("asdasdasdas\n");
		// free(data->envp);
		// char *asd;
		// read(0, asd, 1);
		// kill(0, SIGCHLD);
		// kill(0, SIGCONT);
		ft_exit_num(126, data);
		// ft_exit_num(0, data);
	}
	else
	{
		// printf("%s\n", data->args[0]);
		ft_free_matrix(&data->args);
		g_g = pid;
		signal(SIGQUIT, ft_sign_ign_quit);
		signal(SIGINT, ft_sign_ign_int);
		// signal(SIGSTOP, ft_sign_ign_quit);
		signal(SIGCHLD, ft_kill_child);
		
	// 	char qwe;
	// read(0, &qwe, 1);
		// if ()
		// kill(pid, SIGSTOP);
		waitpid(pid, &status, 0);
		// printf("err:%d\n", status);
		if (!WIFSIGNALED(status))
			errno = status;
		pid = WEXITSTATUS(status);
		if (pid)
			errno = pid;
		// printf("err:%d\n", errno);
		// printf("status: %d\texitstatus: %d\nwifexited: %d\twifsignaled: %d\n", status, WEXITSTATUS(status), WIFEXITED(status), WIFSIGNALED(status));
		// printf("\twstopsig: %d\n", WSTOPSIG(status));
		// printf("\twifcont: %d\n", WIFCONTINUED(status));
		// printf("\twifstop: %d\n", WIFSTOPPED(status));
		// printf("\twtermsig: %d\n", WTERMSIG(status));
		// printf("\tw_exitcode: %d\n", W_EXITCODE(0, status));
		// printf("\tw_exitcode: %d\n", W_EXITCODE(1, status));






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