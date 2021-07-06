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
			// printf("\nx:%d\n", *x);
			ft_arrow_up(line_head, data, *x, len);
			if (*x == -1)
				(*x)++;
		}
	}
	return (1);
}

// int		ft_check_quotes(t_char **line_head)
// {
// 	t_char	*tmp;
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	tmp = *line_head;
// 	while (tmp)
// 	{
// 		if (tmp->buf == '\'')
// 			y++;
// 		else if (tmp->buf == '\"')
// 			x++;
// 		tmp = tmp->next;
// 	}
// 	if (y % 2 || x % 2)
// 		return (0);
// 	return (1);
// }

int	ft_reading(t_char **line_head, int *len, t_data *data)
{	
	char	buf;
	int		x = 0; // per history

	buf = ' ';
	*len = 0;
	while (buf != '\n')
	{
		read(0, &buf, 1);
			// printf("%d\t%c\n", buf, buf);
		if (buf == 27 && ft_read_special(line_head, data, &x, len))
			continue ;
		else if (buf == 12)			// ctrl -l
		{
			// printf("%s", ho);
			// printf("%s\n", cd);
			// ft_write(ho);
			ft_write(tgetstr("ho", NULL));
			ft_write(tgetstr("cd", NULL));
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
			ft_write(tgetstr("cd", NULL));
		
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
			// write(1, "\n", 1);
			write(data->std_fd[1], "\n", 1);
			*len = 0;
			errno = 1;
			return (1);
		}
		else if (buf == 28 || buf == 9)
		{
			//printf("\n%s%s%s\n", tgetstr("up", NULL), tgetstr("bl", NULL), tgetstr("up", NULL));
			continue ;
		}
		else if (buf == 10 && !*len)	// '\n'
		{
			// write(1, &buf, 1);
			write(data->std_fd[1], &buf, 1);
			if(*line_head == NULL)
			 	free(*line_head);
			return (1);
		}
		// write(1, &buf, 1);
		write(data->std_fd[1], &buf, 1);
		ft_buffering(buf, len, line_head);
	}
	return (1);
}


void    ft_read_ops(t_data *data)
{       
    t_char	*line_head;
	t_read	*cmd;
	char	*line;
	int		len;

	len = 0;
	line_head = NULL;
	line = NULL;
	cmd = NULL;
	while (ft_reading(&line_head, &len, data))
	{
		cmd = (t_read *)malloc(sizeof(t_read) * 1);
		cmd->next = NULL;
		if (line_head && line_head->buf != '\n')
		{
		//	if (ft_check_quotes(&line_head))
			// ft_linod_to_line_nofree(&line, len, &line_head);//ft_write("wrong quotes\n");//ft_reading(line_head, len, data);
			// ft_linod_to_line(&cmd->line, len, &line_head);
			ft_linod_to_line(&cmd->line, &line, len, &line_head);
			ft_add_front_read(cmd, data->cmd_head);
			//if (!ft_check_quotes(line, '\'') || !ft_check_quotes(line, '\"'))
			if (!ft_check_quote(line))
				free(line);
			else if (ft_strchr('|', line) != -1)
				ft_exec_pippe(line, data);
			else
				ft_exec_cmd(line, data);
		//	printf("read:%p\n", line);
		//	free(line);
			cmd = cmd->next;
		}
		if (!line_head && !len)
		{
			free(cmd);
			free(line);
			line_head = NULL;
		}
		len = 0;
		line = NULL;
		ft_write("\033[0;32mminishell% \033[0m");
    }
}

