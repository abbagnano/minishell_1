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

int main()
{
	struct termios my_term;
	struct termios my_term2;
	tcgetattr(0, &my_term);
	printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[0]);
	printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);

	
	int optional_action = 0;
	int fildes = 0;	
	/*
	optional_action = 0		// make change immediate 
	optional_action = 1		// drain output, then change == The change should take place after all output written to fd has been read by the master pseudoterminal. Use this value when changing terminal attributes that affect output.
	optional_action = 2		// drain output, flush input == The change should take place after all output written to fd has been sent; in addition, all input that has been received but not read should be discarded (flushed) before the change is made.
	*/

	printf("\n\n\tSETTING_NEW_C_OSPEED\n\n");
	my_term.c_ospeed = 38402;
	tcsetattr(fildes, optional_action, &my_term);

	tcgetattr(0, &my_term);
	printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[0]);
	printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);


	tcgetattr(0, &my_term2);
	printf("input flags==c_iflag : %lu\n", my_term2.c_iflag);
	printf("output flags==c_oflag : %lu\n", my_term2.c_oflag);
	printf("control flags==c_cflag : %lu\n", my_term2.c_cflag);
	printf("local flags==c_lflag : %lu\n", my_term2.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term2.c_cc[0]);
	printf("input speed==c_ispeed : %lu\n", my_term2.c_ispeed);
	printf("output speed==c_ospeed: %lu\n", my_term2.c_ospeed);




	// printf("\n\n\tACTION=1 : DRAIN OUTPUT & THEN CHANGE\n\n");
	// my_term.c_ospeed = 38404;
	// tcsetattr(0, 1, &my_term);
	
	// tcgetattr(0, &my_term);
	// printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	// printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	// printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	// printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	// printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[0]);
	// printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	// printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);

	// printf("\n\n\tACTION=2 : DRAIN OUTPUT & FLUSH INPUT\n\n");
	my_term.c_ospeed = 38400;
	tcsetattr(0, 2, &my_term);
	
	tcgetattr(0, &my_term);
	printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[0]);
	printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);
}