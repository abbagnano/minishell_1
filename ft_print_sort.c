/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/12 10:22:12 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_strstr(char *find, char *str)
{
	while (find && str && *str)
	{
		while (*find && *str == *find)
		{
			str++;
			find++;
			if (!*find)
				return (1);
			else if (*find != *str)
				return (0);
		}
		str++;
	}
	return (0);
}

void	ft_init_pos(t_read **head)
{
	t_read	*tmp;

	tmp = *head;
	while (tmp)
	{
		tmp->pos = 1;
		tmp = tmp->next;
	}
}

int	ft_check_double(t_read **head)
{
	t_read	*tmp;
	t_read	*tmp_x;
	int		num;

	tmp = *head;
	while (tmp)
	{
		num = tmp->pos;
		tmp_x = *head;
		while (tmp_x)
		{
			if (tmp_x->pos == num && ft_strcmp(tmp->line, tmp_x->line))
			{
				if (ft_strcmp(tmp->line, tmp_x->line) < 0)
					tmp_x->pos++;
				else
					tmp->pos++;
				return (1);
			}
			tmp_x = tmp_x->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_get_pos(t_read **head, t_data *data)
{
	t_read	*tmp;
	t_read	*tmp_x;
	int		num;

	data->env_len = 0;
	tmp = *head;
	ft_init_pos(head);
	while (tmp)
	{
		num = tmp->line[0];
		tmp_x = *head;
		while (tmp_x)
		{
			if (tmp_x->line[0] > num)
				tmp_x->pos++;
			tmp_x = tmp_x->next;
		}
		tmp = tmp->next;
		data->env_len++;
	}
	num = ft_check_double(head);
	while (num)
		num = ft_check_double(head);
}

void	ft_print_sort(t_read **head, t_data *data)
{
	t_read	*tmp;
	t_read	*tmp_x;
	int		len;

	tmp = *head;
	len = 1;
	ft_get_pos(head, data);
	tmp = *head;
	while (len <= data->env_len && tmp)
	{
		tmp_x = *head;
		while (tmp_x)
		{
			if (tmp_x->pos == len)
			{
				ft_write(tmp_x->line);
				ft_write("\n");
				len++;
				break ;
			}
			tmp_x = tmp_x->next;
		}
		tmp = tmp->next;
	}
}
