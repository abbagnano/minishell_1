
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int back_stdout;
	int fd_out;
	int fd_in;

	printf("before\n");

	back_stdout = dup(1);

	fd_out = open("outfile", O_RDWR | O_CREAT, 0666);
	printf(" fd_out1: %d\n", fd_out);
	dup2(fd_out, 1);
	printf(" fd_out2: %d\n", fd_out);
	close(fd_out);
	printf("after\n");
	
	dup2(back_stdout,1);
	close(back_stdout);
	printf("after2\n");

	return (0);
}