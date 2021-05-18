NAME	=	minishell
OBJS	=	minishell.o
CFLAGS	=	-Wall -Wextra #-Werror

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	gcc $(CFLAGS) $^ -o $@

%.o		:	%.c
	gcc -c $(CFLAGS) $^

clean	:
	rm -rf $(OBJS)

fclean	:	clean
	rm -rf $(NAME)

re		:	fclean all

PHONY	:	all clean fclean re