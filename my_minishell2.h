/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_minishell2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:23:52 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/06 17:01:25 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MINISHELL2_H
# define MY_MINISHELL2_H

#ifndef MY_MINISHELL
# define MY_MINISHELL
# include "my_minishell.h"
#endif

#include <fcntl.h>





int		ft_check_if_is_execve(char *line, t_data *data);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif