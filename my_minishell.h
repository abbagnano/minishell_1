#ifndef MY_MINISHELL_H
# define MY_MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <termios.h>

#include <sys/ioctl.h>

// typedef struct s_flag
// {
// 	int		tot_com;
// 	int		comma;
// 	int		pipe;
// 	int		infile;
// 	int		outfile;
// 	int		append;
// 	int		dollar;
// }	t_flag;

typedef struct s_char
{
	unsigned char			buf;
	struct s_char	*prev;
	struct s_char	*next;
}	t_char;

typedef struct s_read
{
	char			*line;
	int				pos;
	struct s_read	*next;
}	t_read;

typedef struct	s_data
{
	struct termios old_term;
	struct termios my_term;
	//t_char	**line_head;
//	t_read	**history;
	t_read	**cmd_head;
	t_read	**env_head;
//	t_flag	flags;
	char	**envp;
	int		env_len;
	char	**args;

}	t_data;

/*		minishell.c		*/			
void	ft_no_arg(t_data *data);
void	ft_print_cmd(t_read **head);

/*		ft_exit.c		*/
void	ft_free_env_read(t_read **head);
void	ft_free_read(t_read **head);
void	ft_exit(char *str, t_data *data);

/*		utils_basic.c	*/
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int len);
int		ft_strchr(char c, char *s1);
int		ft_strlen(char *str);
void	ft_write(char *str);

/*		ft_buf_to_list.c	*/
int		ft_buf_to_node(int len, int x, char *buf, t_read *new);
void	ft_append_read(t_read *new, t_read **head);
void	ft_buf_to_list(char *buf, t_data *data);

/*		ft_read_ops.c	*/
int		ft_read_special(t_char **line_head, t_data *data, int *x, int *len);
int     ft_reading(t_char **line_head, int *len, t_data *data);
void	ft_read_ops(t_data *data);

/*		ft_exec_cmd.c	*/
void	ft_cd(char *line, t_data *data);
void	ft_pwd(char *line, t_data *data);
void	ft_echo(char *line, t_data *data);
void	ft_check_cmd(char *line, t_data *data);
void	ft_exec_cmd(char *line, t_data *data);

/*		ft_get_env.c	*/
void	ft_unset(char *line, t_data *data);
void	ft_env(char *line, t_data *data);
void	ft_export(char *line, t_data *data);
void	ft_get_env(char **env, t_data *data);

/*		utils_get_env.c	*/
char	*ft_itoa_errno(int num, int len, char *var);
void	ft_list_to_matr(t_read **env_head, char ***envp, t_data *data);
void	ft_fix_env(char **line);
int		ft_search_env(char *line, int x, int len, t_data *data);
void	ft_add_env(char *line, t_data *data);

/*		ft_print_sort.c	*/
int		ft_strstr(char *find, char *str);
void	ft_init_pos(t_read **head);
int		ft_check_double(t_read **head);
void	ft_get_pos(t_read **head, t_data *data);
void	ft_print_sort(t_read **head, t_data *data);

/*		ft_init_term.c	*/
void	ft_init_term(t_data *data);

/*	ft_arrow.c	*/
void	ft_arrow_up(t_char **line_head, t_data *data, int x, int *len);


void	ft_env_line(char **line, t_data *data);

/*		utils_read_ops.c	*/
int		ft_read_len(t_read **cmd_head);
void	ft_add_front_read(t_read *new, t_read **head);
void	ft_linod_to_line(char **line, char **line2, int len, t_char **line_head);
// void	ft_linod_to_line(char **line, int len, t_char **line_head);
// void	ft_linod_to_line_nofree(char **line, int len, t_char **line_head);
void	ft_buffering(char buf, int *len, t_char **line_head);

/*		utils_t_char.c		*/
int		ft_char_len(t_char **line_head);
void	ft_free_char(t_char **line_head);
void	ft_write_char(t_char **line_head);
void	ft_canc_char(t_char **line_head);

/*		ft_check_quotes.c	*/
int		ft_check_quotes(char *line, char c);
// int		ft_check_quotes(t_char **line_head);
// int		ft_check_quotes_clean(t_char **line_head, char c);

#endif
