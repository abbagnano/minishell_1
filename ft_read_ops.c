#include "my_minishell.h"

int	ft_read_special(t_char **line_head, t_data *data, int *x, int *len)
{
	char	buf;
	int		max_cmd;

	max_cmd = ft_read_len(data->cmd_head);
	read(0, &buf, 1);
	if (buf == '[')
	{
		read(0, &buf, 1);
		if (buf == 'A' && *x < max_cmd)
		{
			(*x)++;
			ft_arrow_up(line_head, data, *x - 1, len);
		}
		else if (buf == 'B' && *x >= 0)
		{
			if (*x == max_cmd)
				(*x)--;
			(*x)--;
			ft_arrow_up(line_head, data, *x, len);
			if (*x == -1)
				(*x)++;
		}
	}
	return (1);
}

int	ft_ctrl_d(char buf, t_char **line_head)
{
	buf = '\0';
	if (*line_head == NULL)
	{
		free(*line_head);
		return (0);
	}
	return (1);
}

int	ft_ctrl_c_read(t_char **line_head, int *len, t_data *data)
{
	if (*line_head)
	{
		ft_free_char(line_head);
		*line_head = NULL;
	}
	write(data->std_fd[1], "\n", 1);
	*len = 0;
	errno = 1;
	return (1);
}

int	ft_reading(t_char **line_head, int *len, t_data *data)
{	
	char	buf;
	int		x;

	buf = ' ';
	x = 0;
	while (buf != '\n')
	{
		read(0, &buf, 1);
		if (buf == 27 && ft_read_special(line_head, data, &x, len))
			continue ;
		else if (buf == 28 || (buf == 12 && ft_ctrl_l(line_head)))
			continue ;
		else if (buf == 9 || (buf == 127 && ft_canc(line_head, len)))
			continue ;
		else if (buf == 4 && !ft_ctrl_d(buf, line_head))
			return (0);
		else if (buf == 3 && ft_ctrl_c_read(line_head, len, data))
			return (1);
		else if (buf == 10 && *len == 0)
			return (ft_new_line(line_head, buf, data));
		write(data->std_fd[1], &buf, 1);
		ft_buffering(buf, len, line_head);
	}
	return (1);
}

void	ft_read_ops(t_char *line_head, t_read *cmd, t_data *data)
{
	char	*line;
	int		len;

	len = 0;
	line = NULL;
	while (ft_reading(&line_head, &len, data))
	{
		cmd = (t_read *)malloc(sizeof(t_read) * 1);
		cmd->next = NULL;
		if (line_head && line_head->buf != '\n')
		{
			ft_linod_to_line(&cmd->line, &line, len, &line_head);
			ft_add_front_read(cmd, data->cmd_head);
			if (!ft_check_quote(line))
				free(line);
			else if (ft_strchr('|', line) != -1)
				ft_exec_pippe(line, data);
			else
				ft_exec_cmd(line, data);
			cmd = cmd->next;
		}
		ft_restart_reading(line_head, &len, cmd, line);
	}
}
