/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/06 14:02:14 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int ft_check_if_is_execve(char *line, t_data *data)
{
	(void)data;
	printf("line:%s\n", line);
	char *path;
	path = getenv("PATH");
	printf("Get_env %s\n", path);
	
	int i = 0;
	while (path[i])
	{
		
				
		if (path[i] == ':')
			printf("num:%d\n", i);
		
		i++;
	}
	
	
	return (0);
}