#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

typedef struct	s_data
{
	int		dup_stdout;
	char	**sort_av;
}				t_data;

/*	utils_pipex.c	*/
int		ft_strchr(char c, char *s1);
int		ft_strncmp(char *s1, char *s2, int len);
int		ft_strlen(char *s1);
void	ft_find_path_env(int *x, char **env);
void	ft_infile_to_sort(t_data *data, char *infile);

/*	pipex.c		*/
char	**ft_opt_to_sort(char *s1, char **sort_av, int y, int z);
int		ft_change_path(char *cmd, t_data *data, int *x, char *env);
void	ft_get_cmd_options(char *cmd, t_data *data);
void	ft_find_cmd(char *cmd, char *env, t_data *data);

/*	ft_exit.c	*/
void	ft_exit(char *s, t_data *data);

/*	ft_pipe.c	*/
void	ft_pipe(char **av, t_data *data);

#endif