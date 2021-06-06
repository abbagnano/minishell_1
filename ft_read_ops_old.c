#include "my_minishell.h"

// void	ft_read_ops(t_data *data)
// {
// 	char	*buf;
// 	int		r;

// 	r = 1;
// 	while (r > 0)
// 	{
// 		buf = (char *)malloc(sizeof(char) * 1024);
// 		buf[1023] = '\0';
// 		r = read(0, buf, 1023);
// 		buf[r] = '\0';
// 		if (buf[0] == '\0')
// 		{
// 			free(buf);
// 			return ;
// 		}
// 		ft_buf_to_list(buf, data);
// 		free(buf);
// 		ft_exec_cmd(data);
// 		ft_write("\033[0;32mminishell% \033[0m");
// 	}
// }

void	ft_linod_to_line(char **line, t_data *data)
{
	t_char	*tmp;
	int		x;

	x = 0;
	*line = (char *)malloc(sizeof(char) * (data->line_len + 1));
	tmp =  *data->line_head;
	while (tmp)
	{
		(*line)[x++] = tmp->buf;
	//	printf("buf: %c\n", tmp->buf);
		tmp = tmp->next;
	}
	(*line)[x] = '\0';
	while (*data->line_head)
	{
		tmp = *data->line_head;
		*data->line_head = (*data->line_head)->next;
		free(tmp);
	}
}

void	ft_buffering(char buf, t_data *data)
{
	t_char	*new;
	t_char	*tmp;

	new = (t_char *)malloc(sizeof(t_char) * 1);
	new->buf = buf;
	new->next = NULL;
	tmp = NULL;
	if (*data->line_head == NULL)
	{
		new->prev = NULL;
		*data->line_head = new; 
	}
	else
	{
		tmp = *data->line_head;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	data->line_len++;
	// ft_append_char(new, data);
	// tmp = *data->line_head;
	// while (tmp)
	// {
	// 	printf("buffering: %c\n", tmp->buf);
	// 	tmp = tmp->next;
	// }

}

void	ft_read_special(t_data *data)
{
	char buf;

	read(0, &buf, 1);
	if (buf == '[')
	{
		read(0, &buf, 1);
		if (buf == 'A')
			printf("arrowww_up\n");
		else if (buf == 'B')
			printf("arrowww_down\n");
		else if (buf == 'C')
			printf("arrowww_right\n");
		else if (buf == 'D')
			printf("arrowww_left\n");
	}
	(void)data;
}


void	ft_read_ops(t_data *data)
{
//	char	*line;
	char	buf;
	int		r;

	r = 1;
	buf = ' ';
	while (buf != '\0' && r > 0)
	{
		while (buf != '\n')
		{
			r = read(0, &buf, 1);
			//	printf("%d\t%c\n", buf, buf);
			if (buf == 27)
			{
				ft_read_special(data);
				continue ;
			}
			else if (buf == 4)
			{
				buf = '\0';
				if(*data->line_head == NULL)
					return ;
			}
			// else
		
				write(1, &buf, 1);
				//if (buf != '\'' && buf != '\"')
					ft_buffering(buf, data);
			// }
		}
		buf = ' ';
		ft_linod_to_line(&line, data);
	//	ft_linod_to_line(data->cmd_head, data);
	//	printf("\n\nline: %s\n\n", *data->cmd_head->line);
		printf("\n\nline: %s\n\n", line);
		ft_buf_to_list(line, data);
		ft_exec_cmd(data);
		free(line);
		ft_write("\033[0;32mminishell% \033[0m");
	}
}
