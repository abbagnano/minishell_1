#include <termios.h>
#include <stdio.h>

/*
tcsetattr, tcgetattr			https://opensource.apple.com/source/xnu/xnu-344.49/bsd/sys/termios.h.auto.html
*/

/*								https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-tcsetattr-set-attributes-terminal  
struct termios {
	tcflag_t==unsigned long			c_iflag;			// input flags 
	tcflag_t==unsigned long			c_oflag;			// output flags 
	tcflag_t==unsigned long			c_cflag;			// control flags 
	tcflag_t==unsigned long			c_lflag;			// local flags 
	cc_t	==unsigned char			c_cc[NCCS];			// control chars 
	speed_t	==long					c_ispeed;			// input speed 
	speed_t	==long					c_ospeed;			// output speed 
};
*/
	#include <unistd.h>	
	#include <termios.h>

int main()
{
	
	struct termios my_term;

	tcgetattr(0, &my_term);
	// printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	// printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	// printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	// printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[VMIN]);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[VTIME]);	
	// printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	// printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);

	char buf;
	int r = 1;
	
	// my_term.c_lflag &= (ICANON|ECHO);
	// tcsetattr(0,0,&my_term);

	r = read(0, &buf, 1);


	printf("buf: %c\n", buf);


	// termios-p->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
	cfmakeraw(&my_term);




	tcgetattr(0, &my_term);
	// printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	// printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	// printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	// printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[VMIN]);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[VTIME]);	
	// printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	// printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);







}