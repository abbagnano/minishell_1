#include "my_minishell.h"

void	free_pipes(int **pipes, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		free((pipes)[i]);
	free(pipes);
}

int	close_all_fd_pipe(int **fd_pipe, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
	}	
	return (0);
}

void	ft_pipe_exit(char *line, char **matr, t_data *data)
{
	if (dup2(data->std_fd[0], 0) == -1 || dup2(data->std_fd[1], 1) == -1)
		ft_exit(strerror(errno), data);
	ft_free_matrix(&matr);
	free(line);
	tcsetattr(0, 0, &data->my_term);
}

void	ft_child(int *x, int **fd_pipes, char *matrx, t_data *data)
{
	ft_pipe_redir(x[0], x[1], fd_pipes, data);
	ft_exec_cmd(matrx, data);
	free_pipes(fd_pipes, x[1]);
	ft_exit_num(errno, data);
}
