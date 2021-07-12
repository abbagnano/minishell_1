/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exportline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:23:37 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:23:38 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_check_format(char c)
{
	if (c == '_' || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| c == '=' || c == 39 || c == 34)
		return (1);
	return (0);
}

int	ft_error_export(void)
{
	ft_write_2("export: not a valid identifier");
	errno = 1;
	return (1);
}

int	ft_check_spaces(char *str, int *x)
{
	while (str[*x] == ' ')
		(*x)++;
	if (!str[*x])
		return (0);
	return (1);
}

void	ft_check_empty(char **str)
{
	int		len;

	len = ft_strlen(*str);
	if ((*str)[len - 1] == '\'' && (*str)[len - 2] == '\'')
	{
		(*str)[len - 1] = '\0';
		(*str)[len - 2] = '\0';
		return ;
	}
}

int	ft_last_spaces(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] == ' ')
		x++;
	if (str[x])
		return (0);
	return (1);
}
