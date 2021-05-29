#ifndef MY_MINISHELL_H
# define MY_MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>

typedef struct s_read
{
	char			*line;
	int				pos;
	struct s_read	*next;
}	t_read;

typedef struct	s_data
{
	t_read	**cmd_head;
	t_read	**env_head;
	int		env_len;
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

/*		ft_read_ops.c	*/
int		ft_buf_to_node(int len, int x, char *buf, t_read *new);
void	ft_append_read(t_read *new, t_read **head);
void	ft_buf_to_list(char *buf, t_data *data);
void	ft_read_ops(t_data *data);

/*		ft_exec_cmd.c	*/
void	ft_cd(char *line, t_data *data);
void	ft_pwd(char *line, t_data *data);
void	ft_echo(char *line, t_data *data);
void	ft_check_cmd(char *line, t_data *data);
void	ft_exec_cmd(t_data *data);

/*		ft_get_env.c	*/
void	ft_unset(char *line, t_data *data);
void	ft_env(char *line, t_data *data);
void	ft_export(char *line, t_data *data);
void	ft_get_env(char **env, t_data *data);

/*		utils_get_env.c	*/
void	ft_fix_env(char **line);
int		ft_search_env(char *line, int len, t_data *data);
void	ft_add_env(char *line, t_data *data);

/*		ft_print_sort.c	*/
int		ft_strstr(char *find, char *str);
void	ft_init_pos(t_read **head);
int		ft_check_double(t_read **head);
void	ft_get_pos(t_read **head, t_data *data);
void	ft_print_sort(t_read **head, t_data *data);

#endif