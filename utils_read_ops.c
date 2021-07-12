/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:24:34 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:24:35 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_read_len(t_read **cmd_head)
{
	t_read	*tmp;
	int		x;

	x = 0;
	tmp = *cmd_head;
	while (tmp)
	{
		tmp = tmp->next;
		x++;
	}
	return (x);
}

void	ft_add_front_read(t_read *new, t_read **head)
{
	t_read	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		*head = new;
		new->next = tmp;
	}
}

void	ft_linod_to_line(char **line, char **line2, int len, t_char **line_head)
{
	t_char	*tmp;
	int		x;

	x = 0;
	*line = (char *)malloc(sizeof(char) * len);
	*line2 = (char *)malloc(sizeof(char) * len);
	tmp = *line_head;
	while (tmp->next)
	{
		(*line)[x] = tmp->buf;
		(*line2)[x++] = tmp->buf;
		tmp = tmp->next;
	}
	(*line)[x] = '\0';
	(*line2)[x] = '\0';
	while (*line_head)
	{
		tmp = *line_head;
		*line_head = (*line_head)->next;
		free(tmp);
	}
}

void	ft_buffering(char buf, int *len, t_char **line_head)
{
	t_char	*new;
	t_char	*tmp;

	new = (t_char *)malloc(sizeof(t_char) * 1);
	new->buf = buf;
	new->next = NULL;
	tmp = NULL;
	if (*line_head == NULL)
	{
		new->prev = NULL;
		*line_head = new;
	}
	else
	{
		tmp = *line_head;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	(*len)++;
}

void	ft_restart_reading(t_char *line_head, int *len,	t_read *cmd)
{
	if (!line_head && *len == 0)
	{
		free(cmd);
		line_head = NULL;
	}
	*len = 0;
	ft_write("\033[0;32mminishell% \033[0m");
}
