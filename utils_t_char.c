/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:24:44 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:24:45 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

int	ft_char_len(t_char **line_head)
{
	t_char	*tmp;
	int		x;

	x = 0;
	tmp = *line_head;
	while (tmp)
	{
		tmp = tmp->next;
		x++;
	}
	return (x);
}

void	ft_free_char(t_char **line_head)
{
	t_char	*tmp;

	while (*line_head)
	{
		tmp = *line_head;
		*line_head = (*line_head)->next;
		free(tmp);
	}
}

void	ft_write_char(t_char **line_head)
{
	t_char	*tmp;

	tmp = *line_head;
	while (tmp)
	{
		write(1, &tmp->buf, 1);
		tmp = tmp->next;
	}
}

void	ft_canc_char(t_char **line_head)
{
	t_char	*tmp;

	tmp = *line_head;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (tmp->next)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
	else
	{
		free(*line_head);
		*line_head = NULL;
	}
}
