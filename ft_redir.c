/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:26:04 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/09 16:45:01 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int ft_strchr_last(char *line, char c)
{
	int	i;
	int r;
	
	i = 0;
	r = -1;
	while (line[i])
	{
		if (line[i] == c)
			r = i;
		i++;
	}
	return (r);
}

int ft_infile(char *line)
{
	int i;
	int c;
	int len;
	char *temp;
	int r;

	r = 0;
	c = 0;
	len = ft_strlen(line);
	while (line[c] && line[c] == ' ')
		c++;
	i = c;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
		i++;
	temp = ft_substr(line, c, i - c);
	r = open(temp, O_RDONLY);
	printf("temp:%s\n", temp);
	if (r > 0)
	{
		printf("ok_fd\n");
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
	int len;
	char *temp;
	int r;

	r = 0;
	c = 0;
	len = ft_strlen(line);
	while (line[c] && line[c] == ' ')
		c++;
	i = c;
	while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>')
		i++;
	temp = ft_substr(line, c, i - c);
	r = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	printf("temp:%s\n", temp);
	if (r > 0)
	{
		printf("ok_fd\n");
	 	dup2(r, 1);
	 	close (r);
	}
	free(temp);
	return (r);
}

int		ft_redir(char *line, t_data *data)
{
	int i;
	int r;
	int back_stdin;
	int back_stdout;
	char **split;
	char *command;
	
	split = ft_split(line, ' ');
	i = 0;
	command = NULL;
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
					// (split[i - 1][1] && split[i - 1][1] != '>')
				)	||
				(
					split[i - 1][0] &&
					(split[i - 1][0] == '<' || 
					split[i - 1][0] == '>'
					) && 
					(
						split[i - 1][1] && split[i - 1][1] == '>' && split[i - 1][2] 
					) ||
					(
						split[i - 1][1] && split[i - 1][1] != '>'
					)
				)
				)
			{	
				printf("char: %c\n", split[i -1][1]);
				command = split[i];
				printf( "command: %s\n",command );
				break ;
			}	
		}
		i++;
	}
	if (command)
	{
	}
	back_stdin = dup(0);
	back_stdout = dup(1);
	i = ft_strchr_last(line, '<');
	if (i  != -1)
	{
		if (ft_infile(line + i + 1) < 0)
		// if (r < 0)
		{	
			printf("Error fd\n");
			exit(0);										////////////////////////////SETTARE
		}
	}
	i = ft_strchr_last(line, '>');
	if (i  != -1)
	{
		if (ft_infile(line + i + 1) < 0)
		{	
			printf("Error fd\n");
			exit(0);										////////////////////////////SETTARE
		}
	}



	////RETURN TO STANDARD IN/OUT
	dup2(back_stdout,1);
	close(back_stdout);
	dup2(back_stdin, 0);
	close(back_stdin);

	// printf("line_out :%s\n", line);	
	return (0);
}