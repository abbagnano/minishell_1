/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_minishell2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:23:52 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/07 09:00:03 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MINISHELL2_H
# define MY_MINISHELL2_H


#include "my_minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*ft_is_execve*/
int		ft_check_if_is_execve(char *line, t_data *data);
int		ft_do_execve(t_data *data);
/*ft_utils_aviol*/
char	**ft_split(char const *s, char c);
/*ft_utils_aviol2*/
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
int		ft_free_matrix(char ***matrix);
#endif