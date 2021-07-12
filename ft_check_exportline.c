/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_exportline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:19:03 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:19:05 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	ft_env_join(char **str, t_data *data)
{
	t_read	*tmp;
	int		len;

	len = ft_strchr('=', *str);
	tmp = *data->env_head;
	while (tmp)
	{
		if (tmp && ft_strncmp(*str, tmp->line, len) == -18
			&& !ft_strncmp(*str, tmp->line, len - 1))
		{
			ft_check_empty(&tmp->line);
			*str = ft_strjoin(tmp->line, *str + len + 1);
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_check_exportline(char *str, int x, int fix, t_data *data)
{
	if (str[x] == '=' && ft_error_export())
		return ;
	while (str[x] && str[x] != '=')
	{
		if (str[x] == ' ')
		{
			if (ft_check_spaces(str, &x) && ft_error_export())
				return ;
			else
				break ;
		}
		if (x != 0 && str[x] == '+' && str[x + 1] == '=' && ++fix)
		{
			ft_env_join(&str, data);
			break ;
		}
		if (ft_check_format(str[x]))
			x++;
		else if (ft_error_export())
			return ;
	}
	if ((!str[x] || (str[x] == '=' && !str[x + 1])) && ++fix)
		ft_fix_env(&str);
	ft_add_env(str, fix, data);
}

void	ft_len_new(char **new, char *str)
{
	int	z;

	z = 0;
	while (str[z] && str[z] != ' ')
	{
		if (str[z] == 39)
		{
			z++;
			while (str[z] && str[z] != 39)
				z++;
		}
		else if (str[z] == 34)
		{
			z++;
			while (str[z] && str[z] != 34)
				z++;
		}
		z++;
	}
	*new = (char *)malloc(sizeof(char) * (z + 1));
}

void	ft_find_arg(char *str, int *x, int y, char ***matr)
{
	char	**new;
	int		z;
	int		a;

	new = (char **)malloc(sizeof(char *) * (y + 2));
	y = ft_cpy_matr(*matr, new);
	ft_len_new(&new[y], str);
	a = 0;
	z = 0;
	while (str[z + a] && str[z + a] != ' ')
	{
		if (str[z + a] == 39 || str[z + a] == 34)
			ft_utils_quotes(&a, &z, str, &new[y]);
		if (!str[z + a])
			break ;
		new[y][z] = str[z + a];
		z++;
	}
	new[y][z] = '\0';
	new[++y] = NULL;
	if (str[z + a] == ' ')
		z++;
	*x += z + a;
	free(*matr);
	*matr = new;
}

void	ft_matrline(char *str, t_data *data)
{
	char	**matr;
	int		x;
	int		y;

	matr = NULL;
	x = 0;
	y = 0;
	while (str[x])
	{
		ft_find_arg(str + x, &x, y, &matr);
		y++;
	}
	x = 0;
	while (matr[x])
		ft_check_exportline(matr[x++], 0, 0, data);
	x = 0;
	while (matr[x])
		free(matr[x++]);
	free(matr);
}
