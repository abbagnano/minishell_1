/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/15 11:59:49 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int	ft_find_command(char **split)
{	
	int	i;

	i = 0;
	while(split[i])
	{
		if (ft_strchr('<', split[i]) == -1 && ft_strchr('>', split[i]) == -1)
		{
			if	(i == 0 || 
				(i > 0 && split[i - 1][0] && split[i - 1][0] != '<' &&
						split[i - 1][0] != '>') ||
				(i > 0 && split[i - 1][0] && (split[i - 1][0] == '<' ||
						split[i - 1][0] == '>') && 
					((i > 0 && split[i - 1][1] && split[i - 1][1] == '>' &&
						split[i - 1][2]) ||
					(i > 0 && split[i - 1][1] && split[i - 1][1] != '>'))))
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

int	ft_command(char *line, t_data *data)
{
	char	**split;
	int		i;
	int		x;
	
	x = 0;
	i = -1;
	split = ft_split(line, ' ');
	if (split)
		i = ft_find_command(split);
	if (i >= 0)
	{
		int c = i;
		while (split[c] && (ft_strchr('<', split[c]) == -1 && ft_strchr('>', split[c]) == -1))
		 	c++;
		data->args = (char **)malloc(sizeof(char *) * (c - i + 1));
		if (!data->args)
			return(0);
		data->args[c - i] = NULL;
		while (i < c)
		{
		 	data->args[x] =ft_strdup(split[i]);
			if (!data->args[x])
				return (0);
			x++;
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_type_of_redir(char *line, int *i)
{
	int	flag;
		
	flag = 0;
	if (line[*i] == '<' && line[*i + 1] && line[*i + 1] != '<')
	{
		if (line[*i + 1] == '>')
		{
			(*i)++;
			flag = 2;
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
	
	return (flag);
}

char	*ft_name_of_file(char *line, int i)
{
	int	c;
	
	(i)++;
	while(line[i] && line[i] == ' ')
		(i)++;
	c = i;
	while(line[c] && line[c] != '<' && line[c] != '>' && line[c] != ' ')
		c++;
	if (c == i)
		return (NULL);
	return(ft_substr(line, i, c - i));
}

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
				if (ft_strncmp(buf,file, ft_strlen(file)) == '\n' || buf[0] == '\0')
				{
					close(fd);
					break;
				}
				write(fd, buf, ft_strlen(buf));
				dup2(back_stdout,1);			
				write(1, ">", 1);
			}
			fd = open("/tmp/minishell", O_RDONLY, 0666);
			dup2(fd, 0);
			close(fd);
		}
	}
	return (0);		
}			
	
int		ft_redir(char *line, t_data *data)
{
	int i;
	int r;
	int back_stdin;
	int back_stdout;


	back_stdin = dup(0);
	back_stdout = dup(1);
	r = ft_command(line, data);
	i = 0;
	int flag = 0;
	char *file;
	int pid;
	int status;

	while (line[i])
	{
		flag = ft_type_of_redir(line,&i);
		
		if (flag > 0)
		{
			file = ft_name_of_file(line,i);
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
		}
		i++;
	}
	if (r == 1)
	{
		r = ft_check_execve(NULL, data);
		if ( r == 1)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(data->args[0], data->args, data->envp);
				printf( "child: execve failed\n");
				printf(" 1\n");
				exit(1);   //TOGLIERE
			}
			else
			{
					// printf(" child\n");
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
			printf("to do: error\n");
			exit(1);    //TOGLIERE
		}
	}
	else
	{
		//RETURN TO STANDARD IN/OUT
		// printf(" parent\n");
		dup2(back_stdout,1);
		close(back_stdout);
		dup2(back_stdin, 0);
		close(back_stdin);
	}
	return (0);
}

/* ERRORS:
	<infile >outfile >> outfile2
	Segmentation fault: 11

	bash-3.2$ <infile >outfile >>outfile2 cat DEVE PRENDERE SOLO IL SECONDO, STESSO DISCORSO SE INVERTITI


	<giusto<sbagliato deve creare il giusto
	
	<<>infile
	<>infile 
	<>>infile
	
	><<infile
	><infile
	>><infile 


	2>&1 > dirlist


	cat infile >outfile non funziona
*/

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