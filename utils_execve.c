#include "my_minishell.h"

void	ft_sign_ign_quit(int sig)
{
	ft_write("Quit: 3\n");
	errno = 128 + sig;
}

void	ft_sign_ign_int(int sig)
{
	ft_write("\n");
	errno = 128 + sig;
}

void	ft_kill_child(int sig)
{
	kill(g_pid, SIGTERM);
	if (!errno)
		errno = 128 + sig;
}

void	ft_execve_failed(char *line, t_data *data)
{
	dup2(data->std_fd[1], 1);
	dup2(data->std_fd[0], 0);
	ft_write_2(strerror(errno));
	ft_free_matrix(&data->args);
	free(line);
	ft_exit_num(126, data);
}
