/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:55:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/12 10:22:05 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	ft_print_env(t_read **head)
{
	t_read	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strstr("=''", tmp->line))
		{	
			ft_write(tmp->line);
			ft_write("\n");
		}
		tmp = tmp->next;
	}
}

void	ft_unset(char *line, t_data *data)
{
	int	len;
	int	x;

	len = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	while (line[x + len] && (line[x + len] != ' ' && line[x + len] != '='))
		len++;
	if (!line[x])
	{
		return ;
	}
	else
		ft_search_env(line + x, len, data);
	ft_list_to_matr(data->env_head, &data->envp, data);
}

void	ft_env(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_env(data->env_head);
	else
	{
		ft_write("bad option or too many arguments\n");
		errno = 1;
	}
}

void	ft_export(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (!line[x])
	{
		ft_print_sort(data->env_head, data);
		return ;
	}
	ft_matrline(line + x, data);
}

void	ft_get_env(char **env, t_data *data)
{
	int		x;
	t_read	*new;

	x = 0;
	while (env[x])
	{
		new = (t_read *)malloc(sizeof(t_read) * 1);
		new->line = ft_strdup(env[x]);
		new->pos = 1;
		new->next = NULL;
		ft_append_read(new, data->env_head);
		x++;
	}
	data->env_len = x;
	data->envp = (char **)malloc(sizeof(char *) * (x + 1));
	x = 0;
	while (x < data->env_len)
	{
		data->envp[x] = env[x];
		x++;
	}
	data->envp[x] = NULL;
}
