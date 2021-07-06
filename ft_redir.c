/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/21 12:14:42 by aviolini         ###   ########.fr       */
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
		if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<' && line[*i + 1] == '>')
			flag = 5;
		else if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<')
			flag = 1;
		else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] != '>' && line[*i + 1] == '<')
			flag = -1;
		else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] != '>')		
			flag = 2;
		else if (line[*i] == '>' && line[*i + 1] && line[*i  + 1] == '>' && line[*i  + 2] && line[*i + 2] == '>')
			flag = -1;
		else if (line[*i] == '>' && line[*i + 1] && line[*i  + 1] == '>')
			flag = 3;
		else if (line[*i] == '<' && line[*i + 1] && line[*i  + 1] == '<' && line[*i  + 2] && line[*i + 2] == '<')
			flag = -1;
		else if (line[*i] == '<' && line[*i + 1] && line[*i  + 1] == '<')
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
	if (file == NULL)
		return (0);
	if (flag == 1)
		return (ft_flag_1(file));
	else if (flag == 2)
		return (ft_flag_2(file));
	else if (flag == 3)
		return (ft_flag_3(file));
	else if (flag == 4)
		return (ft_flag_4(file, data));
	else if (flag == 5)
		return (ft_flag_5(file));
	// free(file);
	return (0);
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
			if (i > x && (i == 0 || flag < 3))
			{
				if (ft_clean_line(*line, &new_line, i, x) == 0)
					return(0);
			}
			else if (i > x)
			{
				if (ft_clean_line(*line, &new_line, i - 1, x) == 0)
					return(0);
			}
			file = ft_name_of_file(*line,i, &x);
			if (ft_open_file(file, flag, data) == 0)
				return (0);							//FARE IL FREE PRIMA DEL RETURN
			free(file);								//IL FREE SI PUO FARE ANCHE NELLA FUNZIONE FT_OPEN_FILe
		}
		if (flag == -1)								
			return (0);							//FARE IL FREE PRIMA DEL RETURN	
	}
	if (i > x)
	{
		if (ft_clean_line(*line, &new_line, i, x) == 0)
			return (0);
	}
	free(*line);
	*line = new_line;
	// printf("qewqweeqw\n");
	return (1);
}


// int	ft_flag_4(char *file, t_data *data)
// {
// 	int	fd;
	
// 	// dup2(data->std_fd[0], 0);
// 	// int back = dup(1);
// 	// dup2(data->std_fd[1],1);
// 	fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
// 	if (fd > 0)
// 	{
// 		int r = 1;
// 		char buf[1024];
		
// 		write(data->std_fd[1], ">", 1);
// 		while (r > 0)
// 		{
// 			//dup2(back, 1);
// 			r = read(data->std_fd[0], buf, 1024);
// 			buf[r] = '\0';
// 			int len = ft_strlen(file);
// 			if ((ft_strncmp(buf, file, len + 1) == '\n' && ft_strncmp(buf, file, len) == 0) || buf[0] == '\0')
// 			{
// 				close(fd);
// 				break;
// 			}
// 			write(fd, buf, ft_strlen(buf));
// 			// dup2(data->std_fd[1],1);			
// 				// printf("buf: %s\n", buf);
// 				// printf("len:%d\n", len);
// 			write(data->std_fd[1], ">", 1);
// 		}
// 		// close(back);
// 		fd = open("/tmp/minishell", O_RDONLY, 0666);
// 		 dup2(fd, 0);
// 		close(fd);
// 	}
// 	else
// 		printf("Error: 6\n");		
// 	return (1);
// }



// int	ft_open_file(char *file, int flag, t_data *data)
// {
// 	int	fd;
	
// 	if (file == NULL)
// 		return (0);						//RETURN -1?
// 	if (flag == 1)
// 	{
// 		fd = open(file, O_RDONLY);
// 		if (fd > 0)
// 		{
// 			printf(" opened\n");
// 			dup2(fd, 0);
// 			close(fd);
// 		}
// 		else
// 			printf("Error: 3\n");
// 	}
// 	else if (flag == 2 || flag == 3)
// 	{
// 		if (flag == 2)
// 			fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
// 		else
// 		// else if (flag == 3)
// 			fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
// 		if (fd > 0)
// 		{
// 			printf(" opened\n");
// 			dup2(fd, 1);
// 			close (fd);	
// 		}
// 		else
// 			printf("Error: 4\n");
// 	}
// 	else if (flag == 4)
// 	{
// 		dup2(data->std_fd[0], 0);
// 		int back = dup(1);
// 		dup2(data->std_fd[1],1);
// 		fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
// 		if (fd > 0)
// 		{
// 			// printf("opened <<\n");
// 			// printf("file:%s\n", file);
// 			int r = 1;
// 			char buf[1024];
			
// 			write(1, ">", 1);
// 			while (r > 0)
// 			{
// 				dup2(back, 1);
// 				r = read(0, buf, 1024);
// 				buf[r] = '\0';
// 				int len = ft_strlen(file);
// 				if ((ft_strncmp(buf, file, len + 1) == '\n' && ft_strncmp(buf, file, len) == 0) || buf[0] == '\0')
// 				{
// 					close(fd);
// 					break;
// 				}
// 				write(fd, buf, ft_strlen(buf));
// 				dup2(data->std_fd[1],1);			
// 					// printf("buf: %s\n", buf);
// 					// printf("len:%d\n", len);
// 				write(1, ">", 1);
// 			}
// 			close(back);
// 			fd = open("/tmp/minishell", O_RDONLY, 0666);
// 			dup2(fd, 0);
// 			close(fd);
// 		}
// 		else
// 			printf("Error: 6\n");	
// 	}
// 	else if (flag == 5)
// 	{
// 		fd = open(file, O_RDWR, 0666);
// 		if (fd < 0)
// 			fd = open(file, O_RDWR | O_CREAT | O_TRUNC , 0666);
// 		if (fd > 0)
// 		{
// 			printf(" opened flag 5\n");
// 			dup2(fd, 0);
// 			close(fd);
// 		}
// 		else
// 			printf("Error: 7\n");
// 	}
// 	// free(file);
// 	return (0);
// }




// int	ft_type_of_redir(char *line, int *i)
// {

// 	int	flag;
		
// 	flag = 0;
// 	ft_slide_quotes(line, i);
// 	if (line[*i])
// 	{
// 		if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<')
// 		{
// 			if (line[*i + 1] == '>')
// 			{
// 				(*i)++;
// 				flag = 5;
// 			}
// 			else
// 				flag = 1;
// 		}
// 		else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] != '>')
// 		{			
// 			if (line[*i + 1] == '<')
// 				printf("Error: 7\n");
// 			flag = 2;
// 		}
// 		else if (line[*i] == '>' && line[*i + 1] && line[*i  + 1] == '>')
// 		{
// 			if (line[*i  + 2] && line[*i + 2] == '>')
// 				printf("Error: 1\n");
// 			(*i)++;
// 			flag = 3;
// 		}
// 		else if (line[*i] == '<' && line[*i + 1] && line[*i  + 1] == '<')
// 		{
// 			if (line[*i  + 2] && line[*i + 2] == '<')
// 				printf("Error: 6\n");
// 			(*i)++;
// 			flag = 4;
// 		}
// 	}
// 	return (flag);
// // }





	// r = ft_check_execve(new_line, data);
	// if (new_line)
	// 	free(new_line);
	// if (r == 1)
	// 	ft_do_execve(data);
	// return (0);
		// return(0);


		// if ( r == 1)
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		// int i = 0;
		// 		// while (data->args[i])
		// 		// 	printf("data->args: %s\n", data->args[i++]);
		// 		execve(data->args[0], data->args, data->envp);
		// 		printf( "child: execve failed\n");
		// 		printf(" 1\n");
		// 		exit(1);   //TOGLIERE
		// 	}
		// 	else
		// 	{
		// 			// printf(" child\n");			
		// 		ft_free_matrix(&data->args);
		// 		waitpid(pid, &status, 0);
		// 		dup2(data->std_fd[1],1);
		// 		close(data->std_fd[1]);
		// 		dup2(data->std_fd[0], 0);
		// 		close(data->std_fd[0]);
		// 		printf(" parent: success\n");
		// 		// exit(0);
		// 		if (WIFEXITED(status)  && !WEXITSTATUS(status))
		// 			return (0);			//SUCCESS
		// 		else 
		// 			return (1);			//NOT SUCCESS
		// 	}
		// }
		// else 
		// {
		// 		// dup2(data->std_fd[1],1);
		// 		// close(data->std_fd[1]);
		// 		// dup2(data->std_fd[0], 0);
		// 		// close(data->std_fd[0]);
		// 		printf("no command\n");
		// }





	// }
	// else
	// {
	// 	//RETURN TO STANDARD IN/OUT
	// 	// printf(" parent\n");
		
	// 	dup2(back_stdout,1);
	// 	close(back_stdout);
	// 	dup2(back_stdin, 0);
	// 	close(back_stdin);
	// }
// 	return (0);
// }



// int	ft_find_command(char **split)
// {	
// 	int	i;

// 	i = 0;
// 	while(split[i])
// 	{
// 		if (ft_strchr('<', split[i]) == -1 && ft_strchr('>', split[i]) == -1)
// 		{
// 			if	(i == 0 || 
// 				(i > 0 && split[i - 1][0] && split[i - 1][0] != '<' &&
// 						split[i - 1][0] != '>') ||
// 				(i > 0 && split[i - 1][0] && (split[i - 1][0] == '<' ||
// 						split[i - 1][0] == '>') && 
// 					((i > 0 && split[i - 1][1] && split[i - 1][1] == '>' &&
// 						split[i - 1][2]) ||
// 					(i > 0 && split[i - 1][1] && split[i - 1][1] != '>'))))
// 			{
// 				return (i);
// 			}
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// int	ft_command(char *line, t_data *data)
// {
// 	char	**split;
// 	int		i;
// 	int		x;
// 	int		r;
// 	char *save;
	
// 	x = 0;
// 	i = -1;
// 	r = 0;
// 	split = ft_split(line, ' ');
// 	if (!split)
// 		return (0);
// 	i = ft_find_command(split);
// 	if (i >= 0)
// 	{
// 		int c = i;
// 		// while (split[c] && (ft_strchr('<', split[c]) == -1 && ft_strchr('>', split[c]) == -1))
// 		// 	c++;
// 		while (split[c])
// 		{
// 			x = 0;
// 			// int len = ft_strlen(split[c]);
// 			while (split[c][x] && (split[c][0] != '<' || split[c][0] != '>'))
// 			{
// 				if (split[c][x] == '<' || split[c][x] == '>')
// 				{
// 					save = split[c];
// 					split[c] = ft_substr(split[c], 0, x);
// 					free(save);
// 					break ;
// 				}
// 				x++;
// 			}
// 			c++;
// 		} 
// 		x = 0;
// 		data->args = (char **)malloc(sizeof(char *) * (c - i + 1));
// 		if (!data->args)
// 			return(0);
// 		data->args[c - i] = NULL;
// 		while (i < c)
// 		{
// 		 	data->args[x] =ft_strdup(split[i]);
// 			if (!data->args[x])
// 				return (0);
// 			x++;
// 			i++;
// 		}
// 		r = 1;
// 		// return (r);
// 	}
// 	ft_free_matrix(&split);
// 	return (r);
// }




/////*old*//////////////////////////////////////////////////////////////
	// i = ft_strchr_last_single(line, '<');
	// if (i  != -1)
	// {
	// 	if (ft_infile(line + i + 1) < 0)
	// 	// if (r < 0)
	// 	{	
	// 		printf("Error fd\n");
	// 		exit(0);										////////////////////////////SETTARE
	// 	}
	// }
	// i = ft_strchr_last_single(line, '>');
	// if (i  != -1)
	// {
	// 	if (ft_outfile(line + i + 1) < 0)
	// 	{	
	// 		printf("Error fd\n");
	// 		exit(0);										////////////////////////////SETTARE
	// 	}
	// }
	// i = ft_strchr_last_double(line, '>');
	// if (i  != -1)
	// {
	// 	if (ft_outfile_app(line + i + 2) < 0)
	// 	{	
	// 		printf("Error fd\n");
	// 		exit(0);										////////////////////////////SETTARE
	// 	}
	// }
//////////////////////////////////////
/*
int ft_strchr_last_single(char *line, char c)
{
	int	i;
	int r;
	
	i = 0;
	r = -1;
	while (line[i])
	{
		if (line[i] == c && line[i + 1])
		{
			if (line[i + 1] != c)
				r = i;
			else if (line[i + 1] == c && c == '>')
				i += 2;
			else if (line[i + 1] == c)// && c == '<')
			{
				printf("Érror\n");
				return (-2);
			}
		}
		i++;
	}
	return (r);
}

int ft_strchr_last_double(char *line, char c)
{
	
	int	i;
	int r;
	i = 0;
	r = -1;
	while (line[i])
	{
		if (line[i] == c && line[i + 1] && line[i + 1] == c)
		{
			r = i;
		}	
		i++;
	}
	return (r);
}

int ft_infile(char *line)
{
	int i;
	int c;
	char *temp;
	int r;

	r = 0;
	c = 0;
	while (line[c] && line[c] == ' ')
		c++;
	i = c;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
		i++;
	temp = ft_substr(line, c, i - c);
	r = open(temp, O_RDONLY);
	// printf("infile:%s\n", temp);
	if (r > 0)
	{
		// printf("ok_fd\n");
	 	dup2(r, 0);
	 	close (r);
	}
	free(temp);
	return (r);
}

int ft_outfile(char *line)
{
	int i;
	int c;
	char *temp;
	int r;

	r = 0;
	c = 0;
	while (line[c] && line[c] == ' ')
		c++;
	i = c;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
		i++;
	temp = ft_substr(line, c, i - c);
	r = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	// printf("outfile:%s\n", temp);
	if (r > 0)
	{
		// printf("ok_fd\n");
	 	dup2(r, 1);
	 	close (r);
	}
	free(temp);
	return (r);
}

int ft_outfile_app(char *line)
{
	int i;
	int c;
	char *temp;
	int r;

	r = 0;
	c = 0;
	while (line[c] && line[c] == ' ')
		c++;
	i = c;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
		i++;
	temp = ft_substr(line, c, i - c);
	r = open(temp, O_RDWR | O_CREAT | O_APPEND, 0666);
	// printf("outfile_app:%s\n", temp);
	if (r > 0)
	{
		// printf("ok_fd\n");
	 	dup2(r, 1);
	 	close (r);
	}
	free(temp);
	return (r);
}
*/