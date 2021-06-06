/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_minishell2.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:23:52 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/06 13:45:13 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MINISHELL2_H
# define MY_MINISHELL2_H

#ifndef MY_MINISHELL
# define MY_MINISHELL
# include "my_minishell.h"
#endif

int		ft_check_if_is_execve(char *line, t_data *data);
char	**ft_split(char const *s, char c);

#endif