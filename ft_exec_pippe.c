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

void	ft_exec_pippe(char *line, t_data *data)
{
	int		x;
	int		**fd;
	char	**matr;
	int pid;
	int pippe;


	x = 0;
	pid = 0;
	while (line[x])
	{
		if (line[x] == '|')
			pid++;
		x++;
	}

	fd = (int **)malloc(sizeof(int *) * pid);
	x = 0;
	while (x < pid)
	{
		fd[x] = (int *)malloc(sizeof(int) * 2);
		x++;
	}
	x = 0;
	while (x < pid)
	{
		pipe(fd[x]);
		x++;
	}
	matr = ft_split(line, '|');
	x = 0;
	pippe = pid;
	while ( x <= pippe)
	// while (matr[x])
	{
	
			pid = fork();
			if (pid == 0)
			{
				if (x != 0)
				{
					dup2(fd[x - 1][0], 0);
				}
				if (x != pippe)
					dup2(fd[x][1], 1);
				// if (matr[x + 1])
				// 	dup2(fd[x][1], 1);
		//		close(fd[x][1]);
		//		close(fd[x][0]);
				close_all_fd_pipe(fd, pippe);
				// printf("-%s-\t%d\n", matr[x], x);
				ft_exec_cmd(matr[x], data);
				free_pipes(fd, pippe);						///////
				ft_exit("", data);
			}
		//	else
		//	{
		//		printf("\tpid: %d\n", pid);
				// wait(NULL);
	// close_all_fd_pipe(fd, pippe);
		//		close(fd[x - 1][0]);
				// close(fd[x][1]);
				x++;
		//	}
	}
//	printf("pid: %d\n", pid);
	close_all_fd_pipe(fd, pippe);
	x = -1;
	while (++x <= pippe)
		wait(NULL);
//	close_all_fd_pipe(fd, pippe);
	free_pipes(fd, pippe);							//////
//	dup2(data->std_fd[1], 1); // data->std_fd[0]);		//	sembra indifferente 
//	close(data->std_fd[1]);								// sembra indifferente
	dup2(data->std_fd[0], 0); // data->std_fd[0]);		// questo lascia aperto ./minishell in reading
//	close(data->std_fd[0]);							// se si aggiunge questo si killa ./minishell
	x = 0;
	while (matr[x])
		free(matr[x++]);
	free(matr);
	free(line);
	tcsetattr(0, 0, &data->my_term);

		// close(fd[1]);
}


// void	ft_exec_pippe(char *line, t_data *data)
// {
// 	int		x;
// 	// int		*fd;
// 	char	**matr;

// 	int fd[2];
// 	// fd = (int *)malloc(sizeof(int) * 2);

// 	// int r = 
// 	pipe(fd);

// 	// printf("%d\n", r);


// 	matr = ft_split(line, '|');
// 	x = 0;
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], 1); //data->std_fd[1]);
// 		// close(data->std_fd[1]);
// 		// close(fd[1]);
// 		ft_exec_cmd(matr[x], data);
// 		ft_exit("closing 1st child\n", data);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		x++;
// 		while (matr[x + 1])
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				close(fd[1]);
// 				dup2(fd[1], 1);
// 				// close(fd[1]);
// 				// dup2(fd[0], 0); // data->std_fd[0]);
// 				// close(fd[0]);
// 				ft_exec_cmd(matr[x], data);
// 				ft_exit("closing 2nd\n", data);
// 			}
// 			else
// 			{
// 				wait(NULL);
// 				x++;
// 				close(fd[1]);
// 				dup2(fd[0], 0); //data->std_fd[0]);
// 				close(fd[0]);
// 				ft_exec_cmd(matr[x], data);
// 				// ft_exit("closing 3rd\n", data);
// 			}
// 		}
// 		// else
// 		// {
// 				// close(fd[1]);
// 				// dup2(fd[0], 0); // data->std_fd[0]);
// 				// close(fd[0]);
// 				// ft_exec_cmd(matr[x], data);
// 				// x++;
// 				// ft_exit("closing bond\n", data);
// 		// }
// 		dup2(data->std_fd[1], 1); // data->std_fd[0]);
// 		close(data->std_fd[1]);
// 		dup2(data->std_fd[0], 0); // data->std_fd[0]);
// 		close(data->std_fd[0]);

// 	}

// 	// while (matr[x])
// 	// {
// 	// 	// dup2(fd[1], 1);//data->std_fd[1]);
// 	// 	// close(fd[1]);
// 	// 	ft_exec_cmd(matr[x], data);
// 	// 	// dup2(fd[0], data->std_fd[0]);
// 	// 	// close(fd[0]);
// 	// 	// free(matr[x]);
// 	// 	x++;
// 	// }
	
// 	free(matr);
// 	free(line);
// 	//ft_exit("pippe\n", data);
// }
