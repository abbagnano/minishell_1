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

void	ft_linod_to_line(char **line, int len, t_char **line_head)
{
	t_char	*tmp;
	int		x;

	x = 0;
//	*line = (char *)malloc(sizeof(char) * (len + 1));
	*line = (char *)malloc(sizeof(char) * len);
	tmp =  *line_head;
	while (tmp->next)
	{
		(*line)[x++] = tmp->buf;
	//	printf("buf: %c\n", tmp->buf);
		tmp = tmp->next;
	}
	(*line)[x] = '\0';
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
	// ft_append_char(new, data);
	// tmp = *data->line_head;
	// while (tmp)
	// {
	// 	printf("buffering: %c\n", tmp->buf);
	// 	tmp = tmp->next;
	// }

}

int	ft_read_len(t_read **cmd_head)
{
	t_read *tmp;
	int x;

	x = 0;
	tmp = *cmd_head;
	while(tmp)
	{
		tmp = tmp->next;
		x++;
	}
	return (x);
}

int	ft_char_len(t_char **line_head)
{
	t_char *tmp;
	int x;

	x = 0;
	tmp = *line_head;
	while(tmp)
	{
		tmp = tmp->next;
		x++;
	}
	return (x);
}


//void	ft_read_special(t_data *data)
int	ft_read_special(t_char **line_head, t_data *data, int *x, int *len)
{
	char	buf;
	int		max_cmd;


	max_cmd = ft_read_len(data->cmd_head);
	// printf("%d\tx: %d\n", max_cmd)
	
	read(0, &buf, 1);
	if (buf == '[')
	{
		read(0, &buf, 1);
		if (buf == 'A' && *x < max_cmd)
		{
		//	printf("%s", tgetstr("dl", &bp));
	//		if (*x != 0)
	//			(*x)++;
				(*x)++;
			ft_arrow_up(line_head, data, *x - 1, len);//printf("arrowww_up\n" );
	//		if (*x == 0)
			//if (*x < max)
			
		}
		else if (buf == 'B' && *x > 0)
		{
			if (*x == max_cmd)
				(*x)--;
			(*x)--;
			ft_arrow_up(line_head, data, *x, len);
		
		//	printf("arrowww_down\n");
		}

		// }
	}
		//printf("del\n");

	return (1);
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
	t_char *tmp;

	tmp = *line_head;
	while(tmp)
	{
		write(1, &tmp->buf, 1);
		tmp=tmp->next;
	}
}

void	ft_canc_char(t_char **line_head)
{
	t_char *tmp;

	tmp = *line_head;
	while(tmp->next && tmp->next->next)
		tmp=tmp->next;
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

int	ft_reading(t_char **line_head, int *len, t_data *data)
{	
	char	buf;
	int		x = 0; // per history
	char	*ho;
	char	*cd;
	char	*up;

	tgetent(NULL, getenv ("TERM"));
	ho = tgetstr("ho", NULL);
	cd = tgetstr("cd", NULL);
	up = tgetstr("up", NULL);
	buf = ' ';
	*len = 0;
	while (buf != '\n')
	{
		read(0, &buf, 1);
		//	printf("%d\t%c\n", buf, buf);
		if (buf == 27 && ft_read_special(line_head, data, &x, len))
			continue ;
		else if (buf == 12)			// ctrl -l
		{
			// printf("%s", ho);
			// printf("%s\n", cd);
			ft_write(ho);
			ft_write(cd);
			ft_write("\033[0;32mminishell% \033[0m");
			ft_write_char(line_head);
			continue ;
		}
		else if (buf == 127) //&& *line_head)// && *len > 1)		// canc
		{
			if (!*line_head)
				continue ;
			// printf("\n%s%s%s\n%s", up, cd, up, cd);
			ft_write(tgetstr("le", NULL));
			ft_write(cd);
		
		//	 ioctl(1, TIOCFLUSH); 
		
			ft_canc_char(line_head);
		//	ft_write("\033[0;32mminishell% \033[0m");
		//	ft_write_char(line_head);
			*len = ft_char_len(line_head);
			// printf("len: %d\n", *len);
			continue ;
		}
		else if (buf == 4)			// ctrl -d
		{
			buf = '\0';
			if(*line_head == NULL)
			{
				free(*line_head);
				return (0);
			}
		}
		else if (buf == 3)			//	ctrl-c
		{
			if(*line_head)
			{
				ft_free_char(line_head);
				*line_head = NULL;
			}
			write(1, "\n", 1);
			*len = 0;
			return (1);
		}
		else if (buf == 28)
		{
			//printf("\n%s%s%s\n", tgetstr("up", NULL), tgetstr("bl", NULL), tgetstr("up", NULL));
			continue ;
		}
		else if (buf == 10 && !*len)	// '\n'
		{
			write(1, &buf, 1);
			if(*line_head == NULL)
			 	free(*line_head);
			return (1);
		}
		write(1, &buf, 1);
		ft_buffering(buf, len, line_head);
	}
	// free(ho);
	// free(cd);
	// free(up);
	return (1);
}

// void	ft_print_read(t_read **cmd_head)
// {
// 	t_read *tmp;
// 	tmp = *cmd_head;
// 	printf("ghj\n");
// 	while(tmp)
// 	{
// 		printf("cmd:%s\n", tmp->line);
// 		tmp=tmp->next;
// 	}
// }

// void	ft_print_char(t_char **line_head)
// {
// 	t_char *tmp;
// 	tmp = *line_head;
// 	//	printf("%c\n", tmp->buf);
// 		tmp=tmp->next;
// 	while(tmp)
// 	{
// 		printf("prec: %c\t%c\n", tmp->prev->buf, tmp->buf);
// 		tmp=tmp->next;
// 	}
// }

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

void    ft_read_ops(t_data *data)
{       
    t_char	*line_head;
	t_read	*cmd;
	int		len;

	len = 0;

	line_head = NULL;

	while (ft_reading(&line_head, &len, data))
	{
		cmd = (t_read *)malloc(sizeof(t_read) * 1);
		cmd->next = NULL;
		if (line_head && line_head->buf != '\n')
		{
			ft_linod_to_line(&cmd->line, len, &line_head);
			ft_add_front_read(cmd, data->cmd_head);
			ft_exec_cmd(cmd->line, data);
		}
		if (!line_head && !len)
		{
		//	printf("sfddsf   %d\n", len);
			free(cmd);
			line_head = NULL;
		}
		cmd = cmd->next;
		len = 0;
		ft_write("\033[0;32mminishell% \033[0m");
    }
//	if (line_head)
//		free(line_head);
}

