/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:20:06 by arrigo            #+#    #+#             */
/*   Updated: 2021/06/07 13:50:37 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int ft_pipe(char *line, t_data *data)
{
	if (ft_strchr('|', line) == 0)
		return (0);      ////////ERROR
	

	return (0);
}