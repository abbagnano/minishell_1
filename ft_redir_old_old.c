/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/07/08 10:26:33 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

void	ft_slide_quotes(char *line, int *i)
{
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
	}	
}

int	ft_type_of_redir(char *line, int *i)
{
	int	flag;

	flag = 0;
	ft_slide_quotes(line, i);
	if (line[*i])
	{
		if ((line[*i] == '<' || line[*i] == '>') && !(line[*i + 1]))
			flag = -1;
		else if (line[*i] == '<' && line[*i + 1] &&	line[*i + 1] != '<' && line[*i + 1] == '>')
			flag = 5;
		else if (line[*i] == '<' && line[*i + 1] &&	line[*i + 1] != '<')
			flag = 1;
		else if (line[*i] == '>' && line[*i + 1] &&	line[*i + 1] != '>' && line[*i + 1] == '<')
			flag = -1;
		else if (line[*i] == '>' && line[*i + 1] &&	line[*i + 1] != '>')
			flag = 2;
		else if (line[*i] == '>' && line[*i + 1] &&	line[*i + 1] == '>' && line[*i + 2] && line[*i + 2] == '>')
			flag = -1;
		else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
			flag = 3;
		else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<' && \
			line[*i + 2] && line[*i + 2] == '<')
			flag = -1;
		else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
			flag = 4;
		if (flag >= 3)
			(*i)++;
	}
	return (flag);
}

char	*ft_name_of_file(char *line, int i,int *x)
{
	int	c;

	(i)++;
	while(line[i] && line[i] == ' ')
		(i)++;
	if (line[i] == '"')
	{
		(i)++;
		c = i;
		while (line[c] && line[c] != '"')
			c++;
		*x = c + 1;
	}
	else
	{
		c = (i);
		while(line[c] && line[c] != '<' && line[c] != '>' && line[c] != ' ')
			c++;
		*x = c;
	}
	if (c == (i))
		return (NULL);
	return (ft_substr(line, i, c - i));
}

int	ft_flag_1(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_flag_2(char *file)
{
	int	fd;
	
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);	
	if (fd < 0)
		return (0);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	ft_flag_3(char *file)
{
	int	fd;
	
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 1);
	close(fd);
	return (1);
}

void	ft_charrr(t_char **qwe)
{
	t_char *tmp;
	t_char *new;

	new = (t_char *)malloc(sizeof(t_char) * 1);
	new->buf = '\n';
	new->next = NULL;
	if (!*qwe)
	{
		*qwe = new;
		return ;
	}
	tmp = *qwe;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_ctr_c(int *fd)
{
	close(*fd);
	*fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (*fd < 0)
		return (0);
	write(*fd, "\0", 1);
	return (1);
}

int	ft_flag_4(char *file, t_data *data)
{
	int		fd;
	int		r;
	char	*buf;//[1024];
	char	*buf2;
	int		len;
	//FARE UNLINK DEL TEMP;

	r = 1;
	fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	write(data->std_fd[1], ">", 1);

	t_char *qwe = NULL;
	// t_char *tmp = qwe;
	tcsetattr(0, 0, &data->my_term);
	while (ft_reading(&qwe, &len, data)) // (r > 0)
	{
		// r = read(data->std_fd[0], buf, 1024);
		// buf[r] = '\0';
		if (len == 0 && ft_ctr_c(&fd))
			break ;//printf("asd\n");
		ft_charrr(&qwe);
		ft_linod_to_line(&buf, &buf2, len, &qwe);
		len = ft_strlen(file);
		if ((ft_strncmp(buf, file, len + 1) == '\n' && ft_strncmp(buf, file, len) == 0) || buf[0] == '\0')
		{
			free(buf);
			free(buf2);
			break;
		}
		write(fd, buf, ft_strlen(buf));
		write(data->std_fd[1], ">", 1);
		free(buf);
		free(buf2);
		// ft_free_char(&qwe);
		// qwe = NULL;
	}
	close(fd);
	tcsetattr(0, 0, &data->old_term);
	fd = open("/tmp/minishell", O_RDONLY, 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_flag_5(char *file)
{
	int	fd;
	
	fd = open(file, O_RDWR, 0666);
	if (fd < 0)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC , 0666);
	if (fd < 0)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_open_file(char *file, int flag, t_data *data)
{
	int ret;

	if (file == NULL)
		return (0);
	ret = 0;
	if (flag == 1)
		ret = ft_flag_1(file);
	else if (flag == 2)
		ret = ft_flag_2(file);
	else if (flag == 3)
		ret = ft_flag_3(file);
	else if (flag == 4)
		ret = ft_flag_4(file, data);
	else if (flag == 5)
		ret = ft_flag_5(file);
	free(file);
	return (ret);
}

int ft_clean_line(char *line, char **new_line, int i, int x)
{
	char	*temp;

	if (!*new_line)
		*new_line = ft_substr(line, x, i - x);
	else
	{
		temp = ft_substr(line, x, i - x);
		if (!temp)
			return (0);
		if (ft_strjoin_over(new_line, temp) == 0)
			return (0);
		free(temp);
	}
	return (1);
}
	
int ft_redir_error(char *new_line)
{
	if (new_line)
		free(new_line);
	return (0);
}

int	ft_redir(char **line, t_data *data)
{
	int		i;
	char	*new_line;
	int		flag;
	int		x;
	char	*file;

	i = -1;
	x = 0;
	new_line = NULL;
	while ((*line)[++i])
	{
		flag = ft_type_of_redir(*line, &i);
		if (flag > 0)
		{
			if ((i > x) && (i == 0 || flag < 3) && ft_clean_line(*line, &new_line, i, x) == 0)
				return (ft_redir_error(new_line));
			else if ((i > x) && !(i == 0 || flag < 3) && ft_clean_line(*line, &new_line, i - 1, x) == 0)
				return (ft_redir_error(new_line));
			file = ft_name_of_file(*line,i, &x);
			if (ft_open_file(file, flag, data) == 0)
				return (ft_redir_error(new_line));
		}
		if (flag == -1)
			return (ft_redir_error(new_line));					
	}
	if (i > x && ft_clean_line(*line, &new_line, i, x) == 0)
		return (ft_redir_error(new_line));
	free(*line);
	*line = new_line;
	return (1);
}
