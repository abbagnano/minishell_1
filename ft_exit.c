/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:22:46 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/12 10:22:15 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	ft_free_env_read(t_read **head)
{
	t_read	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void	ft_free_read(t_read **head)
{
	t_read	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
}

void	ft_exit_cmd(char *line, t_data *data)
{
	int	x;
	int	tot;

	x = 0;
	tot = 0;
	ft_write("exit\n");
	while (line[x] && line [x] == ' ')
		x++;
	while (line[x] && line[x] >= '0' && line[x] <= '9')
		tot = tot * 10 + line[x++] - 48;
	if (line[x] && line[x] != ' ' && (line[x] < '0' || line[x] > '9'))
		ft_exit_error(data);
	while (line[x] && line [x] == ' ')
		x++;
	if (line[x])
	{
		ft_write_2("minishell: exit: too many arguments");
		errno = 1;
		return ;
	}
	if (errno != 255)
		errno = tot;
	ft_exit_num(errno, data);
}

void	ft_exit_num(int num, t_data *data)
{
	if (*data->cmd_head)
		ft_free_read(data->cmd_head);
	free(data->cmd_head);
	if (*data->env_head)
		ft_free_read(data->env_head);
	free(data->env_head);
	free(data->envp);
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	tcsetattr(0, 0, &data->old_term);
	exit(num);
}

void	ft_exit(char *str, t_data *data)
{
	ft_write(str);
	if (*data->cmd_head)
		ft_free_read(data->cmd_head);
	free(data->cmd_head);
	if (*data->env_head)
		ft_free_read(data->env_head);
	free(data->env_head);
	free(data->envp);
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	tcsetattr(0, 0, &data->old_term);
	exit(0);
}
