#include "my_minishell.h"
#include "my_minishell2.h"


void	ft_exec_pippe(char *line, t_data *data)
{
	int		x;
	int		*fd;
	char	**matr;

	// int fd[2];
	fd = (int *)malloc(sizeof(int) * 2);

	int pid; 
	pipe(fd);

	matr = ft_split(line, '|');
	x = 0;
	while (matr[x])
	{
	
			pid = fork();
			if (pid == 0 && !matr[x + 1])
			{
				printf("\tlast child:%s\n", matr[x]);
				// dup2(fd[0], 0);//	sembra indifferente
				// close(fd[0]);		//	sembra indifferente
				// dup2(fd[1], 1);		//		non fa scrivere a schermo
				// close(fd[1]);		// non fa scrivere a schermo
			
				ft_exec_cmd(matr[x], data);
				ft_exit("", data);
			}
			else if (pid == 0)
			{
				printf("\tchild:%s\n", matr[x]);
				// dup2(fd[0], 0);			//	sembra indifferente
				close(fd[0]);
				dup2(fd[1], 1);			// questo permette di non far scerivere il risultato del child
				// close(fd[1]);			// indifferente
			
				ft_exec_cmd(matr[x], data);
				ft_exit("", data);
			}
			else
			{

			wait(NULL);
			// if (!matr[x + 1])
				x++;
			// if (matr[x + 1])
			// 	continue ;					//	indifferente
			// 	close(fd[1]);
			// printf("\tmaster:%s\n", matr[x]);
			// x++;
			// if (!matr[x + 1])		// indifferente
			// 	close(fd[1]);				// indifferente
			// close (1);
			// dup2(fd[0], 0); //data->std_fd[0]);
			// close(fd[0]);
			// ft_exec_cmd(matr[x], data);
			// ft_exit("closing 3rd\n", data);
		//	if (!matr[x + 1])					// non cambia niente ( pero forse serve fd[0])
				close(fd[0]);				//	questo permette di chiudere la lettura

			}
		// }
		// printf("\t\tend_x:%d\n", x);
	}
			// dup2(data->std_fd[1], 1); // data->std_fd[0]);		//	sembra indifferente 
			// close(data->std_fd[1]);								// sembra indifferente
			dup2(data->std_fd[0], 0); // data->std_fd[0]);		// questo lascia aperto ./minishell in reading
			// close(data->std_fd[0]);							// se si aggiunge questo si killa ./minishell
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