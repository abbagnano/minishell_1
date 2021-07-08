#include "my_minishell.h"

int	ft_init_pipes(char *line, int ***fd_pipes, t_data *data)
{
	int	x;
	int	num_pipes;

	num_pipes = 0;
	x = -1;
	while (line[++x])
		if (line[x] == '|')
			num_pipes++;
	(*fd_pipes) = (int **)malloc(sizeof(int *) * num_pipes);
	if (!(*fd_pipes))
		ft_exit(strerror(errno), data);
	x = -1;
	while (++x < num_pipes)
	{
		(*fd_pipes)[x] = (int *)malloc(sizeof(int) * 2);
		if (!(*fd_pipes)[x])
			ft_exit(strerror(errno), data);
	}
	x = -1;
	while (++x < num_pipes)
		if (pipe((*fd_pipes)[x]) == -1)
			ft_exit(strerror(errno), data);
	return (num_pipes);
}

void	ft_pipe_redir(int x, int num_pipes, int **fd_pipes, t_data *data)
{
	if (x != 0 && dup2(fd_pipes[x - 1][0], 0) == -1)
		ft_exit(strerror(errno), data);
	if (x != num_pipes && dup2(fd_pipes[x][1], 1) == -1)
		ft_exit(strerror(errno), data);
	close_all_fd_pipe(fd_pipes, num_pipes);
}

int	ft_pipe_wait(int pid, int x, int num_pipes, int **fd_pipes)
{
	int	status;

	if (x != 0 && (close(fd_pipes[x - 1][0]) == -1))
		return (0);
	if (x != num_pipes && (close(fd_pipes[x][1]) == -1))
		return (0);
	if (waitpid(pid, &status, 0) == -1)
		return (0);
	if (!WIFSIGNALED(status))
		errno = status;
	status = WEXITSTATUS(status);
	if (status)
		errno = status;
	return (1);
}

void	ft_exec_pippe(char *line, t_data *data)
{
	int		x[2];
	int		**fd_pipes;
	char	**matr;
	int		pid;

	matr = ft_split(line, '|');
	if (!matr)
		ft_exit(strerror(errno), data);
	x[1] = ft_init_pipes(line, &fd_pipes, data);
	x[0] = -1;
	while (++x[0] <= x[1])
	{
		pid = fork();
		if (pid == -1)
			ft_exit(strerror(errno), data);
		if (pid == 0)
		{
			ft_child(x, fd_pipes, matr[x[0]], data);
		}
		if (ft_pipe_wait(pid, x[0], x[1], fd_pipes) == 0)
			ft_exit(strerror(errno), data);
	}
	free_pipes(fd_pipes, x[1]);
	ft_pipe_exit(line, matr, data);
}
