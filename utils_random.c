/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgradia <fgradia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:24:30 by fgradia           #+#    #+#             */
/*   Updated: 2021/07/12 10:24:31 by fgradia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

void	ft_write_2(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	write(2, "\n", 1);
}

void	ft_exit_error(t_data *data)
{
	ft_write_2("minishell: exit: numeric argument required");
	errno = 255;
	ft_exit_num(errno, data);
}

int	ft_free_env(t_read	*tmp, t_data *data)
{
	free(tmp->line);
	free(tmp);
	data->env_len--;
	return (1);
}

int	ft_empty_line(int *len, t_char **line_head)
{
	*len = 0;
	ft_free_char(line_head);
	line_head = NULL;
	return (1);
}

void	ft_check_builtin(char *line, t_data *data)
{
	if (!ft_strncmp(line, "echo ", 5) || ft_strncmp(line, "echo ", 5) == -32)
		ft_echo(line + 4);
	else if (!ft_strncmp(line, "export ", 7)
		|| ft_strncmp(line, "export ", 7) == -32)
		ft_export(line + 6, data);
	else if (!ft_strncmp(line, "env ", 4) || ft_strncmp(line, "env ", 4) == -32)
		ft_env(line + 3, data);
	else if (!ft_strncmp(line, "exit ", 5)
		|| ft_strncmp(line, "exit ", 5) == -32)
		ft_exit_cmd(line + 4, data);
	else if (ft_check_execve(line, data))
		ft_do_execve(line, data);
	else
	{
		ft_write_2("minishell: command not found");
		errno = 127;
	}
}
