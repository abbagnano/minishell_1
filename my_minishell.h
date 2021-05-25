#ifndef MY_MINISHELL_H
# define MY_MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
/*
typedef struct s_list
{
	char			*cmd;
	struct s_list	*next;
}	t_list;
*/
typedef struct s_read
{
	char			*line;
	struct s_read	*next;
}	t_read;

typedef struct	s_data
{
	t_read	*cmd_head;
}	t_data;

/*		minishell.c		*/
int		ft_strlen(char *str);
void	ft_write(char *str);
//void	ft_read(t_list **head);
void	ft_no_arg(t_data *data);

#endif