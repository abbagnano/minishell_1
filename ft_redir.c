/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/17 13:15:49 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

// 

int	ft_type_of_redir(char *line, int *i)
{
	int	flag;
		
	flag = 0;
	int back = i;
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
		(*i)++;
		// printf("ciao\n");
	}
	if (line[*i])
	{
		if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<')
		{
			if (line[*i + 1] == '>')
			{
				(*i)++;
				flag = 5;
			}
			else
				flag = 1;
		}
		else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] != '>')
		{			
			if (line[*i + 1] == '<')
				printf("Error: 7\n");
			flag = 2;
		}
		else if (line[*i] == '>' && line[*i + 1] && line[*i  + 1] == '>')
		{
			if (line[*i  + 2] && line[*i + 2] == '>')
				printf("Error: 1\n");
			(*i)++;
			flag = 3;
		}
		else if (line[*i] == '<' && line[*i + 1] && line[*i  + 1] == '<')
		{
			if (line[*i  + 2] && line[*i + 2] == '<')
				printf("Error: 6\n");
			(*i)++;
			flag = 4;
		}
	}
	return (flag);
}


char	*ft_name_of_file(char *line, int i,int *x)
{
	int	c;

	(i)++;
	while(line[i] && line[i] == ' ')
		(i)++;
	if (line[i] == '"')											//TESTARE BENE
	{
		(i)++;
		c = i;
		while (line[c] && line[c] != '"')
			c++;
		*x = c + 1;
		//c++;
	}
	else
	{
		c = (i);
		while(line[c] && line[c] != '<' && line[c] != '>' && line[c] != ' ')
			c++;
		*x = c;
	}
	if (c == (i))							//TESTARE
		return (NULL);
	char *temp = ft_substr(line, i, c - i);
	printf("temp:%s\n", temp);
	return(temp);
}

// char	*ft_name_of_file(char *line, int i, char **new_line)
// {
// 	int	c;

// 	(i)++;
// 	while(line[i] && line[i] == ' ')
// 		(i)++;
// 	if (line[i] == '"')											//TESTARE BENE
// 	{
// 		i++;
// 		c = i;
// 		while (line[c] && line[c] != '"')
// 			c++;
// 	}
// 	else
// 	{
// 		c = i;
// 		while(line[c] && line[c] != '<' && line[c] != '>' && line[c] != ' ')
// 			c++;
// 	}
// 	if (c == i)							//TESTARE
// 		return (NULL);

// 	return(ft_substr(line, i, c - i));
// }

int	ft_open_file(char *file, int flag,int back_stdin,int back_stdout)
{
	int	fd;
	
	if (flag == 1)
	{
		fd = open(file, O_RDONLY);
		if (fd > 0)
		{
			printf(" opened\n");
			dup2(fd, 0);
			close(fd);
		}
		else
			printf("Error: 3\n");
	}
	else if (flag == 2 || flag == 3)
	{
		if (flag == 2)
			fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		else
		// else if (flag == 3)
			fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (fd > 0)
		{
			printf(" opened\n");
			dup2(fd, 1);
			close (fd);	
		}
		else
			printf("Error: 4\n");
	}
	else if (flag == 4)
	{
		dup2(back_stdin, 0);
		int back = dup(1);
		dup2(back_stdout,1);
		fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd > 0)
		{
			printf("opened <<\n");
			printf("file:%s\n", file);
			int r = 1;
			char buf[1024];
			
			write(1, ">", 1);
			while (r > 0)
			{
				dup2(back, 1);
				r = read(0, buf, 1024);
				buf[r] = '\0';
				int len = ft_strlen(file);
				if ((ft_strncmp(buf, file, len + 1) == '\n' && ft_strncmp(buf, file, len) == 0) || buf[0] == '\0')
				{
					close(fd);
					break;
				}
				write(fd, buf, ft_strlen(buf));
				dup2(back_stdout,1);			
					printf("buf: %s\n", buf);
					printf("len:%d\n", len);
				write(1, ">", 1);
			}
			close(back);
			fd = open("/tmp/minishell", O_RDONLY, 0666);
			dup2(fd, 0);
			close(fd);
		}
		else
			printf("Error: 6\n");	
	}
	else if (flag == 5)
	{
		fd = open(file, O_RDWR, 0666);
		if (fd < 0)
			fd = open(file, O_RDWR | O_CREAT | O_TRUNC , 0666);
		if (fd > 0)
		{
			printf(" opened flag 5\n");
			dup2(fd, 0);
			close(fd);
		}
		else
			printf("Error: 7\n");
	}
	return (0);
}			
	
int		ft_redir(char *line, t_data *data)
{
	int i;
	int r;
	int back_stdin;
	int back_stdout;
	char *new_line;


	new_line = NULL;
	back_stdin = dup(0);
	back_stdout = dup(1);
	// r = ft_command(line, data);
	// r = 1;
	i = 0;
	int flag = 0;
	char *file;
	int pid;
	int status;
	int x;
	int z;

	x = 0;
	while (line[i])
	{
		flag = ft_type_of_redir(line,&i);
		if (flag > 0)
		{
			if (flag < 3)
			{
				z = 0;
			}
			else
			{
				if (x > 0)
					z = 1;
			}
			if (i > x)
			{
				if (!new_line)
				{
					printf("i:%d\n", i);
					printf("x:%d\n", x);	
					new_line = ft_substr(line, x, i - x);
					// exit(0);
				}
				else
				{
					char *save;
					char *temp;
					save = new_line;
					temp = ft_substr(line, x, i - x);
					printf(" temp1:%s\n", temp);
					new_line = ft_strjoin(new_line, temp);
					free(temp);
					free(save);
					// printf("new_line1: %s\n", new_line);
				}
				// x++;
			}
			// printf("i:%d\n", i);
			// printf("x:%d\n", x);
			file = ft_name_of_file(line,i, &x);
			// x = i;
			printf("file:%s\n", file);
			if (file == NULL)
				return (0);
			// if (flag == 4)
			// {
			// 	// dup2(back_stdout,1);
			// 	// close(back_stdout);
			// 	dup2(back_stdin, 0);
			// 	// close(back_stdin);
			// }
			ft_open_file(file, flag, back_stdin, back_stdout);   //RETURN ERROR
			free(file);
			file = NULL;
		}
		i++;
	}
	printf("i:%d\n", i);
	printf("x:%d\n", x);
	
	if (i > x)
	{
		if (!new_line)
		{
			new_line = ft_substr(line, x, i - x);
		}
		else
		{
			char *save;
			char *temp;
			save = new_line;
			temp = ft_substr(line, x, i - x);
			printf(" temp2:%s\n", temp);
			new_line = ft_strjoin(new_line, temp);
			free(temp);
			free(save);
		}
		// x++;
	}	

	
	// printf("new_line2: %s\n", new_line);
	// printf(" strlen: %d\n", ft_strlen(new_line));
	// exit(0);
	// if (r == 1)
	// {
		r = ft_check_execve(new_line, data);
		printf("new_line:%s\n", new_line);
				// free(new_line);	              /////////////////SCOMMENTARE
		if ( r == 1)
		{
			pid = fork();
			if (pid == 0)
			{
				int i = 0;
				while (data->args[i])
					printf("data->args: %s\n", data->args[i++]);
				execve(data->args[0], data->args, data->envp);
				printf( "child: execve failed\n");
				printf(" 1\n");
				exit(1);   //TOGLIERE
			}
			else
			{
					// printf(" child\n");			
				ft_free_matrix(&data->args);
				waitpid(pid, &status, 0);
				dup2(back_stdout,1);
				close(back_stdout);
				dup2(back_stdin, 0);
				close(back_stdin);
				printf(" parent: success\n");
				// exit(0);
				if (WIFEXITED(status)  && !WEXITSTATUS(status))
					return (0);			//SUCCESS
				else 
					return (1);			//NOT SUCCESS
			}
		}
		else 
		{
				dup2(back_stdout,1);
				close(back_stdout);
				dup2(back_stdin, 0);
				close(back_stdin);	
				printf("no command\n");
		}





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
	return (0);
}



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