/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_minishell2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:23:52 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/06 16:54:49 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MINISHELL2_H
# define MY_MINISHELL2_H


#include "my_minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

/*ft_execve*/
int		ft_check_execve(char *line, t_data *data);
void	ft_do_execve(char *line, t_data *data);
/*ft_pipe.c*/
int		ft_pipe(char *line, t_data *data);
/*ft_redir.c*/
int	ft_redir(char **line, t_data *data);
/*ft_utils_aviol*/
char	**ft_split(char const *s, char c);
/*ft_utils_aviol2*/
int	ft_strjoin_over(char **s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
int		ft_free_matrix(char ***matrix);
#endif