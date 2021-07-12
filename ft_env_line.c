/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:19:29 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 11:40:03 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_get_var(char **var, int *len, t_data *data)
{
	t_read	*tmp;

	*len = ft_strlen(*var);
	tmp = *data->env_head;
	while (tmp && (*var)[1] != '?'
		&& ft_strncmp((*var + 1), tmp->line, *len) != -61)
		tmp = tmp->next;
	if ((*var)[1] == '?')
	{
		free(*var);
		*var = ft_itoa_errno(errno);
		*len = 2;
		return (0);
	}
	else
	{
		free(*var);
		*var = "\0";
		if (tmp)
			*var = tmp->line;
	}
	return (1);
}

void	ft_var_line(char *var, char **line, int x, t_data *data)
{
	char	*new;
	int		tot[2];
	int		z;
	int		len;

	tot[0] = ft_get_var(&var, &len, data);
	tot[1] = ft_strlen(*line) - len + ft_strlen(var + len);
	new = (char *)malloc(sizeof(char) * (tot[1] + 1));
	z = -1;
	while (++z < x)
		new[z] = (*line)[z];
	tot[1] = z;
	z = -1;
	while (var[len + ++z])
		new[tot[1] + z] = var[len + z];
	len += tot[1];
	tot[1] += z;
	z = -1;
	while ((*line)[len + ++z])
		new[tot[1] + z] = (*line)[len + z];
	new[tot[1] + z] = '\0';
	free(*line);
	if (!tot[0])
		free(var);
	*line = new;
}

int	ft_env_quotes(int *z, int *x, char *tmp)
{
	while (*z < *x && tmp[*z])
	{
		if (tmp[*z] == 34)
		{
			(*z)++;
			while (*z < *x && tmp[*z] && tmp[*z] != 34)
				(*z)++;
			if (tmp[*z] == 34)
				(*z)++;
			continue ;
		}	
		else if (tmp[*z] == 39)
		{
			(*z)++;
			while (tmp[*z] && tmp[*z] != '\'')
				(*z)++;
			if (*z >= *x)
			{
				*x = *z + 1;
				return (0);
			}
		}
		(*z)++;
	}
	return (1);
}

void	ft_cpy_env(int z, int *len, char *tmp, char *var)
{
	*len = 0;
	while (tmp[z + *len] && tmp[z + *len] != ' ')
	{
		if (var)
			var[*len] = tmp[z + *len];
		(*len)++;
		if (tmp[z + *len] == '$' || tmp[z + *len] == '?'
			|| tmp[z + *len] == '\'' || tmp[z + *len] == '\"')
			return ;
	}
	return ;
}

void	ft_env_line(char **line, int *x, t_data *data)
{
	char	*var;
	int		z;
	int		len;

	z = 0;
	*x += ft_strchr('$', (*line + *x));
	if ((*x < 0 || !(*line)[*x + 1] || (*line)[*x + 1] == ' ') && ++(*x))
		return ;
	if (!ft_env_quotes(&z, x, *line))
		return ;
	ft_cpy_env(z, &len, *line, NULL);
	if ((*line)[z + len] == '?')
		len++;
	var = (char *)malloc(sizeof(char) * (len + 1));
	ft_cpy_env(z, &len, *line, var);
	if ((*line)[z + len] == '?')
	{
		var[len] = (*line)[z + len];
		len++;
	}
	var[len] = '\0';
	ft_var_line(var, line, *x, data);
}
