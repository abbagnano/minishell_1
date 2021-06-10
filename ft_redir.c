/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/10 15:41:58 by aviolini         ###   ########.fr       */
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

int		ft_redir(char *line, t_data *data)
{
	int i;
	int back_stdin;
	int back_stdout;
	char **split;
	char *command;
	(void)data;
	
	*data->args = NULL;
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
				break;
			}
		}
		i++;
	}
	int c = i;
	printf( "i: %d\n", i);
	while (split[c] && (ft_strchr('<', split[c]) == -1 && ft_strchr('>', split[c]) == -1))
	{
	 	c++;
	}

	data->args = (char **)malloc(sizeof(char *) * (c - i + 1));
	data->args[c - i] = NULL;
	int x = 0;
	while (i < c)
	 	data->args[x++] =ft_strdup(split[i++]);
	back_stdin = dup(0);
	back_stdout = dup(1);
	i = ft_strchr_last_single(line, '<');
	if (i  != -1)
	{
		if (ft_infile(line + i + 1) < 0)
		// if (r < 0)
		{	
			printf("Error fd\n");
			exit(0);										////////////////////////////SETTARE
		}
	}
	i = ft_strchr_last_single(line, '>');
	if (i  != -1)
	{
		if (ft_outfile(line + i + 1) < 0)
		{	
			printf("Error fd\n");
			exit(0);										////////////////////////////SETTARE
		}
	}
	i = ft_strchr_last_double(line, '>');
	if (i  != -1)
	{
		if (ft_outfile_app(line + i + 2) < 0)
		{	
			printf("Error fd\n");
			exit(0);										////////////////////////////SETTARE
		}
	}
	if ((*data->args) && ft_check_execve(data->args[0], data))
	{
		int pid;
		int status;
		
		pid = fork();
		if (pid == 0)
		{
			execve(data->args[0], data->args, data->envp);
		}
		else
		{
			waitpid(pid, &status, 0);
			dup2(back_stdout,1);
			close(back_stdout);
			dup2(back_stdin, 0);
			close(back_stdin);
			if (WIFEXITED(status)  && !WEXITSTATUS(status))
				return (0);			//SUCCESS
			else 
				return (1);			//NOT SUCCESS
		}
	}
	else
	{
		//RETURN TO STANDARD IN/OUT
		dup2(back_stdout,1);
		close(back_stdout);
		dup2(back_stdin, 0);
		close(back_stdin);
	}
	// printf("line_out :%s\n", line);	
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
