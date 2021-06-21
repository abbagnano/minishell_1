# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ioctl.h>

// int main(int ac, char **av)
// {	
// 	int pid;
// 	int fd_pipe[2];
// 	int fd = dup(1);

// 	pipe(fd_pipe);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		printf("pid_C:%d\n", pid);
// 		write(fd, "Child\n", 6);
// 		close(fd_pipe[0]);  
// 		dup2(fd_pipe[1], 1);
// 		close(fd_pipe[1]);
// 		execlp(av[1], av[1], NULL);
// 		write(fd, "Failed\n", 7);	
// 	}
// 	else
// 	{
// 		printf("pid_P:%d\n", pid);
// 		write(fd, "Waiting\n", 8);
// 		int w = wait(NULL);
// 		printf("wait:%d\n", w);
// 		write(fd, "Parent\n", 7);
// 		close(fd_pipe[1]);                  //SE COMMENTATO NON CHIUDE IL PROGRAMMA
// 		dup2(fd_pipe[0], 0);
// 		close(fd_pipe[0]);
// 		execlp(av[2], av[2],av[3], NULL);
// 		write(fd, "Failed\n", 7);	
// 	}
// 	return 0;
// }

int main(int ac, char **av)
{	
	int pid;
	int pid2;
	int fd_pipe[2];
	int fd0= dup(0);
	int fd1= dup(1);
	int w;

	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		printf("pid_C:%d\n", pid);
		write(fd1, "Child\n", 6);
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		execlp(av[1], av[1], NULL);
		write(fd1, "Failed\n", 7);	
	}
	else
	{
		printf("pid_P:%d\n", pid);
		write(fd1, "Waiting\n", 8);
		// w = wait(NULL);
		w = waitpid(pid, NULL, 0);		
		printf("wait:%d\n", w);
		write(fd1, "Parent\n", 7);
		pid2 = fork();
		if (pid2 == 0)
		{
			printf("pid2_C2:%d\n", pid2);
			write(fd1, "Child2\n", 7);
			close(fd_pipe[1]);
			dup2(fd_pipe[0], 0);
			close(fd_pipe[0]);
			execlp(av[2], av[2],av[3], NULL);
			write(fd1, "Failed\n", 7);	
		}
		else
		{
			write(fd1, "Waiting\n", 8);
			printf("pid2_Last:%d\n", pid2);
			w = waitpid(pid2, NULL, 0);
			printf("wait:%d\n", w);
			exit(1);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			dup2(fd0, 0);
			close(fd0);
			// dup2(fd1, 1);
			// close(fd1);
			write(fd1, "Ok\n", 3);
		}
	}
	return 0;
}
