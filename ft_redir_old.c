/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:44:47 by arrigo            #+#    #+#             */
/*   Updated: 2021/06/09 09:22:34 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"
#include "my_minishell2.h"

int		ft_redir(char *line, t_data *data)
{
	int infile;
	int outfile;
	int c;
	int i;
	int back_stdin;
	int back_stdout;
	char *save;
	char **split;
	
	split = ft_split(line, ' ');
	back_stdin = dup(0);
	back_stdout = dup(1);

	// i = ft_strchr('<', line);
	c = 0;
	if (split[0][0] == '<' && split[0][1] == '\0')
	{
		infile = open(split[1], O_RDONLY);
		dup2(infile, 0);
		close(infile);
		c = 2;
	}
	
	i = ft_strchr('>', line);
	if (i != -1)
	{
		i = 0;
		while (split[i][0] != '>')
			i++;
		// printf(" i:%d\n", i);
		if (i > 0 && split[i][0] == '>' && split[i + 1])
		{
			if (split[i][1] == '\0')
			{
				outfile = open(split[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
				dup2(outfile, 1);
				close(outfile);
			}
			else if (split[i][1] == '>' && split[i][2] == '\0')
			{
				outfile = open(split[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
				dup2(outfile, 1);
				close(outfile);
			}
		}
	}
	else
	{	
		i = 0;
		while (split[i])
			i++;
	}
	
	free(line);
	line = ft_strdup(split[c]);
	while (++c < i)
	{
		save = line;
		line = ft_strjoin(line, " ");
		free(save);
		save = line;
		line = ft_strjoin(line, split[c]);
		free(save);
	}
	// printf(" line: %s\n", line);
	ft_free_matrix(&split);
	data->args = ft_split(line, ' ');
	if (ft_check_execve(line, data))
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
	return (0);
}