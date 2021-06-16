/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:20:06 by arrigo            #+#    #+#             */
/*   Updated: 2021/06/16 13:46:03 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int ft_pipe(char *line, t_data *data)
{
	(void)data;
	if (ft_strchr('|', line) == 0)
		return (0);      ////////ERROR
	

	return (0);
}