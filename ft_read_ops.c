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


//void	ft_read_special(t_data *data)
int	ft_read_special(t_char **line_head, t_data *data, int *x)
{
	char	buf;
	int		max_cmd;
	int		l;

	max_cmd = ft_read_len(data->cmd_head);
	l = 0;
	
	read(0, &buf, 1);
	if (buf == '[')
	{
		read(0, &buf, 1);
		if (buf == 'A' && *x < max_cmd)
		{
		//	printf("%s", tgetstr("dl", &bp));
			ft_arrow_up(line_head, data, *x);//printf("arrowww_up\n" );
			//if (*x < max)
				(*x)++;
			
		}
		else if (buf == 'B' && *x > 0)
		{
			if (*x == max_cmd)
				(*x)--;
			(*x)--;
			ft_arrow_up(line_head, data, *x);
		
		//	printf("arrowww_down\n");
		}
		// else if (buf == 'C')
		// {
		// 	//printf("\033[1C");
		// 	//printf("arrowww_right\n");//
		// 	printf("%s", tgetstr("nd", NULL));
		// }
		// else if (buf == 'D')
		// {
		// //	printf("\033[1D");
		// 	//printf("arrowww_left\n");
		// //	printf("%s", tgetstr("vi", NULL));
		// //	sleep(2);
		// 	printf("%s", tgetstr("le", NULL));
		// //	sleep(2);
		// //	printf("%s", tgetstr("bl", NULL));
		// 	//printf("%s", tgetstr("ve", NULL));
		// }
	}
		//printf("del\n");
		// printf("%s", tgetstr("kl", NULL));
	//	ft_write(tgetstr("im", NULL));
	//	ft_write(tgetstr("le", NULL));
	//	ft_write(tgetstr("ec", NULL));
	//	ft_write(tgetstr("dc", NULL));
	//	ft_write(tgetstr("ed", NULL));
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
	char	*tc;

//	tc = (char *)malloc(sizeof(char) * 2048);
	tc = NULL;
	tgetent(tc, getenv ("TERM"));
	buf = ' ';
	*len = 0;
	while (buf != '\n')
	{
		read(0, &buf, 1);
		//	printf("%d\t%c\n", buf, buf);
		if (buf == 27 && ft_read_special(line_head, data, &x))
			continue ;
		else if (buf == 12)
		{
			printf("%s", tgetstr("ho", NULL));
			printf("%s\n", tgetstr("cd", NULL));
			//tputs(tgetstr("cd", NULL), 1, write);
			
			ft_write("\033[0;32mminishell% \033[0m");
			ft_write_char(line_head);
			continue ;
		}
		else if (buf == 127 && *line_head)
		{
				printf("%s", tgetstr("up", NULL));
			//	printf("%s", tgetstr("le", NULL));
			// tgoto(tgetstr("cd", NULL), 0 , 0);
			//	tputs(tgoto(tgetstr("cd", NULL), 0, 0), 1, putchar);
			// tputs(tgetstr("le", NULL), 0, putchar);

			// tputs(tgetstr("cd", NULL), 0, putchar);
			// write(1, "\n", 1);
			 printf("%s\n", tgetstr("cd", NULL));
			// tcsetattr(1, 0, &data->my_term);
		//	printf("\t%s", tgetstr("up", NULL));
			ft_canc_char(line_head);
			ft_write("\033[0;32mminishell% \033[0m");
			ft_write_char(line_head);
			continue ;
		}
		else if (buf == 4)
		{
			buf = '\0';
			if(*line_head == NULL)
				return (0);
		}
		write(1, &buf, 1);
		ft_buffering(buf, len, line_head);
	}
	return (1);
}

void	ft_print_read(t_read **cmd_head)
{
	t_read *tmp;
	tmp = *cmd_head;
	printf("ghj\n");
	while(tmp)
	{
		printf("cmd:%s\n", tmp->line);
		tmp=tmp->next;
	}
}

void	ft_print_char(t_char **line_head)
{
	t_char *tmp;
	tmp = *line_head;
	//	printf("%c\n", tmp->buf);
		tmp=tmp->next;
	while(tmp)
	{
		printf("prec: %c\t%c\n", tmp->prev->buf, tmp->buf);
		tmp=tmp->next;
	}
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
		//tmp->next->next = NULL;
	}
}

void    ft_read_ops(t_data *data)
{       
    t_char	*line_head;
	t_read	*cmd;
	int		len;

	len = 0;
//      *data->cmd_head = (t_read *)malloc(sizeof(t_read) * 1);
//	(*data->cmd_head)->line = NULL;
//	(*data->cmd_head)->next = NULL;
	line_head = (t_char *)malloc(sizeof(t_char) * 1);
	line_head = NULL;
//        cmd = (t_read *)malloc(sizeof(t_read) * 1);
//	cmd = NULL;
//	cmd->next = NULL;
        while (ft_reading(&line_head, &len, data))
        {
//        	*data->cmd_head = (t_read *)malloc(sizeof(t_read) * 1);
//		(*data->cmd_head)->line = NULL;
//		(*data->cmd_head)->next = NULL;
        	cmd = (t_read *)malloc(sizeof(t_read) * 1);
//		(*data->cmd_head)->line = NULL;
		cmd->next = NULL;
//		ft_print_char(&line_head);
//              ft_linod_to_line(&(*data->cmd_head)->line, len, &line_head);
			if (line_head)
            {  ft_linod_to_line(&cmd->line, len, &line_head);
//              printf("\n\nline: %s\n\n", (*data->cmd_head)->line);
                // printf("\n\nline: %s\nlen: %d\n", cmd->line, len);
				 printf("line: %s\n", cmd->line);
//		cmd->line[len - 1] = '\0';
	//	ft_append_read(cmd, data->cmd_head);
				ft_add_front_read(cmd, data->cmd_head);
			}
//                cmd = *data->cmd_head;
//		*data->cmd_head = (*data->cmd_head)->next;
//		ft_exec_cmd(cmd->line, data);
		cmd = cmd->next;
		len = 0;
                ft_write("\033[0;32mminishell% \033[0m");
        }
	
	//free(cmd);
}

