/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/10 19:22:13 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

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

int ft_command(char *line, t_data *data)
{
		char **split;
	(void)data;
	int i;
	int r;
	r = 0;
	
	// *data->args = NULL;
	split = ft_split(line, ' ');
	i = 0;
	while(split[i])
	{
		if (ft_strchr('<', split[i]) == -1 && ft_strchr('>', split[i]) == -1)									//TESTARE
		{
			// if (split[i - 1] && ft_strchr('<', split[i - 1]) != 0 && ft_strchr('>', split[i - 1]) != 0)
			// if (split[i - 1][0] && split[i - 1][0] != '<' && split[i - 1][0] != '>')
			// {
			// 	if (!split[i - 1][1] || (split[i - 1][1] != '>' || split[i - 1][0] == '\0'))
				
			// }
			if	(	i == 0 || 
				(	split[i - 1][0] && split[i - 1][0] != '<' && split[i - 1][0] != '>' //&&
				)	||
				(
					i > 0 && split[i - 1][0] &&
					(split[i - 1][0] == '<' || 
					split[i - 1][0] == '>'
					) && 
					((
						i > 0 && split[i - 1][1] && split[i - 1][1] == '>' && split[i - 1][2] 
					) ||
					(
						i > 0 && split[i - 1][1] && split[i - 1][1] != '>'
					))
				)
				)
			{	
				printf(" i:%d\n", i);
				r = 1;
				break ;
			}
		}
		i++;
	}
	if (r == 1)
	{
		int c = i;
		while (split[c] && (ft_strchr('<', split[c]) == -1 && ft_strchr('>', split[c]) == -1))
		{
		 	c++;
		}
		printf( "c: %d\n", c);
		data->args = (char **)malloc(sizeof(char *) * (c - i + 1));
		data->args[c - i] = NULL;
		int x = 0;
		while (i < c)
		 	data->args[x++] =ft_strdup(split[i++]);
	
		i = 0;
		while (data->args[i])
		{
			printf(" data->args[%d]: %s\n",i,  data->args[i]);
			i++;
		}
	}
	return (r);
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
	int c = 0;
	int flag = 0;
	int fd;
	while (line[i])
	{
		flag = 0;
		if (line[i] == '<' && line[i + 1] && line[i + 1] != '<')
			flag = 1;
		else if (line[i] == '>' && line[i + 1] && line[i + 1] != '>')
			flag = 2;
		else if (line[i] == '>' && line[i + 1] && line[i  + 1] == '>')
		{
			i++;
			flag = 3;
		}
		if (flag > 0)
		{
			i++;
			while(line[i] && line[i] == ' ')
				i++;
			c = i;
			while(line[c] && line[c] != '<' && line[c] != '>' && line[c] != ' ')
				c++;
			if (c == i)
				printf(" Error: fd\n");
			char *file = ft_substr(line, i, c - i);
			printf( " substr: %s\n", file);
			printf(" flag: %d\n", flag);
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
					printf("Error\n");
			}
			else if (flag == 2 || flag == 3)
			{
				if (flag == 2)
					fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
				else if (flag == 3)
					fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
				if (fd > 0)
				{
					printf(" opened\n");
					dup2(fd, 1);
					close (fd);	
				}
				else
					printf("Error\n");
			}			
		}
		i++;
	}
// exit(0);
	printf(" r: %d\n", r);
	int f = ft_check_execve(line, data);
			i = 0;
			while (data->args[i])
			{
				printf(" aa_data->args[%d]: %s\n",i,  data->args[i]);
				i++;
			}
	 if (r == 1 && f == 1)
	 {
		int pid;
		int status;
		
		pid = fork();
		if (pid == 0)
		{		
			execve(data->args[0], data->args, data->envp);
			printf( "execve failed\n");
			printf(" 1\n");
						exit(0);
		}
		else
		{
					// printf(" child\n");
			waitpid(pid, &status, 0);
			dup2(back_stdout,1);
			close(back_stdout);
			dup2(back_stdin, 0);
			close(back_stdin);
				printf(" 2\n");
			exit(0);

			if (WIFEXITED(status)  && !WEXITSTATUS(status))
				return (0);			//SUCCESS
			else 
				return (1);			//NOT SUCCESS
		}
	 }
	//  else
	//  {
		//RETURN TO STANDARD IN/OUT
		// printf(" parent\n");
		dup2(back_stdout,1);
		close(back_stdout);
		dup2(back_stdin, 0);
		close(back_stdin);
	// }
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