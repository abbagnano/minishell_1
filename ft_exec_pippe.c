#include "my_minishell.h"
#include "my_minishell2.h"

void free_pipes(int **pipes, int num)
{
	int i;

	i = -1;
	while (++i < num)
		free((pipes)[i]);
	free(pipes);
}

int close_all_fd_pipe(int **fd_pipe, int num)
{
	int i;

	i = -1;
	while (++i < num)
	{
		close(fd_pipe[i][0]);
		close(fd_pipe[i][1]);
	}	
	return (0);
}

// int ft_init_pipes(char *line, t_data *data)
// {
// 	int	x;
// 	int	num_pipes;

// 	num_pipes = 0;
// 	x = -1;


// 	return(num_pipes);
// }


void	ft_exec_pippe(char *line, t_data *data)
{
	int		x;
	int		**fd;
	char	**matr;
	int pid;
	int num_pipes;
	int	status;


	x = -1;
	num_pipes = 0;
	while (line[++x])
	{
		if (line[x] == '|')
			num_pipes++;
	}
	fd = (int **)malloc(sizeof(int *) * num_pipes);
	if (!fd)
		ft_exit(strerror(errno), data);
	x = -1;
	while (++x < num_pipes)
	{
		fd[x] = (int *)malloc(sizeof(int) * 2);
		if (!fd[x])
			ft_exit(strerror(errno), data);
	}
	x = -1;
	while (++x < num_pipes)
	{
		if (pipe(fd[x]) == -1)
			ft_exit(strerror(errno), data);
	}
	matr = ft_split(line, '|');
	if (!matr)
		ft_exit(strerror(errno), data);
	x = -1;
	while ( ++x <= num_pipes)
	{
		pid = fork();
		if (pid == -1)
			ft_exit(strerror(errno), data);
		if (pid == 0)
		{
			if (x != 0 && dup2(fd[x - 1][0], 0) == -1)
				ft_exit(strerror(errno), data);
			if (x != num_pipes && dup2(fd[x][1], 1) == -1)
				ft_exit(strerror(errno), data);
			close_all_fd_pipe(fd, num_pipes);
			ft_exec_cmd(matr[x], data);
			free_pipes(fd, num_pipes);
			ft_exit_num(errno, data);
		}
		if (x != 0)
			close(fd[x - 1][0]);
		if (x != num_pipes)
			close(fd[x][1]);
		if (waitpid(pid, &status, 0) == -1)
			ft_exit(strerror(errno), data);
		if (!WIFSIGNALED(status))
			errno = status;
		pid = WEXITSTATUS(status);
		if (pid)
			errno = pid;
	}
	free_pipes(fd, num_pipes);
	if (dup2(data->std_fd[0], 0) == -1)
		ft_exit(strerror(errno), data);
	x = 0;
	ft_free_matrix(&matr);
	free(line);
	tcsetattr(0, 0, &data->my_term);
}