#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termcap.h>    /* this comes from ncurses, anyway... */
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#define	PRINTC(a,b)	 (printf("%s : %c\n",a,b))
#define	PRINTS(a,b)	 (printf("%s : %s\n",a,b))
#define	PRINTI(a,b)	 (printf("%s : %d\n",a,b))


char *termtype;
char *tgetstr ();
	char term_buffer[1024];
	char **buf_area = NULL;

char *cl_string, *cm_string;
int height;
int width;
int auto_wrap;

char PC;   /* For tputs.  */
char *BC;  /* For tgoto.  */
char *UP;

void interrogate_terminal ()
{
#ifdef Unix
  /* Here we assume that an explicit term_buffer
     was provided to tgetent.  */
  char *buffer
    = (char *) malloc (strlen (term_buffer));
#define BUFFADDR &buffer
#else
#define BUFFADDR 0
#endif

  char *temp;


  /* Extract information we will use.  */
  cl_string = tgetstr ("cl", BUFFADDR);
  cm_string = tgetstr ("cm", BUFFADDR);
  auto_wrap = tgetflag ("am");
  height = tgetnum ("li");
  width = tgetnum ("co");
  BC = tgetstr("bl", BUFFADDR);

  /* Extract information that termcap functions use.  */
  temp = tgetstr ("pc", BUFFADDR);
  PC = temp ? *temp : 0;
  BC = tgetstr ("le", BUFFADDR);
  UP = tgetstr ("", BUFFADDR);
PRINTS("BC", BC);
  PRINTS("UP", UP);





}
///////////////////////////////////////////////////////////////////////////////////
void init_terminal_data ()
{

	// char temp[1024];

	char *buf;

	int success;
  termtype = getenv ("TERM");
	// buf_area = (char **)malloc(1024 * sizeof(char *));
	// *buf_area = (char *)malloc(1024);
	// buf = (char *)malloc(1024);

	if (termtype == 0)
	  printf ("Specify a terminal type with `setenv TERM <yourtype>'.\n");	
	success = tgetent (term_buffer, termtype);
	// printf("success: %d\n", success);
	if (success < 0)
	  printf ("Could not access the termcap data base.\n");
	if (success == 0)
	  printf ("Terminal type `%s' is not defined.\n", termtype);
		printf("term_type: %s\n", termtype);
	printf("term_buffer1: %s\n", term_buffer);
	// read(0, temp, 1024);
	printf("term_buffer2: %s\n", term_buffer);
	// PRINTS("temp", temp);
	// PRINTS("term",termtype);
	printf("tget_co %d\n",tgetnum ("co"));
	printf("tget_li %d\n",tgetnum ("li"));
	// printf("tget_do %d\n",tgetstr ("do", buf));
	buf = NULL;

	struct termios my_term;

	printf("ioctl:%d\n",ioctl(0, TIOCGETA,my_term));
	printf("ioctl:%d\n",ioctl(0, TIOCSTI));

	printf("input flags==c_iflag : %lu\n", my_term.c_iflag);
	printf("output flags==c_oflag : %lu\n", my_term.c_oflag);
	printf("control flags==c_cflag : %lu\n", my_term.c_cflag);
	printf("local flags==c_lflag : %lu\n", my_term.c_lflag);
	printf("control chars==c_cc[NCCS] : %hhu\n", my_term.c_cc[0]);
	printf("input speed==c_ispeed : %lu\n", my_term.c_ispeed);
	printf("output speed==c_ospeed: %lu\n", my_term.c_ospeed);



}

///////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    // clear_screen();
	init_terminal_data();
	interrogate_terminal();
    printf("Hello World!\n");



    return (0);
}