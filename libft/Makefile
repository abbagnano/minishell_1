# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/13 16:48:27 by aviolini          #+#    #+#              #
#    Updated: 2021/06/03 07:15:56 by arrigo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

SRCS =			ft_str_tools.c \
				ft_str_tools2.c \
				ft_str_tools3.c \
				ft_str_tools4.c \
				ft_str_tools5.c \
				ft_str_tools6.c \
				ft_math_tools.c \
				ft_mem_tools.c \
				ft_mem_tools2.c \
				ft_malloc_tools.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_itoa_base.c \
				ft_split.c \
				ft_strtrim.c \
				ft_struct_tools.c \
				ft_matr_tools.c \
				ft_list_add.c \
				ft_list_move.c \
				ft_list_del.c \
				ft_list_find.c \
				ft_list_find2.c \
				ft_list_swap.c \
				ft_list_sort.c \
				ft_list_sort2.c \
				ft_list_tools.c \
				ft_list_print.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_read_fd.c
				
OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

.c.o		:
				$(CC) $(CFLAGS) -c $<

$(NAME)		:	$(OBJS)
				ar rc $(NAME) $(OBJS)

all			:	$(NAME)

clean		:		
				$(RM) $(OBJS)
		
fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
