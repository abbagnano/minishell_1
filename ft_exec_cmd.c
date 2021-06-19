#include "my_minishell.h"
#include "my_minishell2.h"

void	ft_cd(char *line, t_data *data)
{
	int	ret;
	int	x;

	if (ft_strncmp(line, "cd ", 3) == -32)		//se il comando è solo "cd" senza path allora non fa niente
		return ;
	x = 0;
	while (line[x] == ' ')
		x++;
	ret = chdir(line + x);
	if (ret == -1)
	{
		ft_write(strerror(errno));
		ft_write("\n");
	}

	(void)data;
}

void	ft_pwd(char *line, t_data *data)
{
	char	*path;

	path = NULL;
//	path = getcwd(path, 1);
	path = getcwd(NULL, 0);
	ft_write(path);
	ft_write("\n");
	free(path);

	(void)data;
	(void)line;	//	aggiungere check se ci sono comandi dopo il pwd
}

void	ft_echo(char *line, t_data *data)
{
	int	x;
	int	new_line;

	x = 0;
	new_line = 1;
	// printf("echosss: %s\n", line);
	while (line[x] == ' ')
		x++;
	if ((!ft_strncmp(line + x, "-n ", 3) || ft_strncmp(line + x, "-n ", 3) == -32) && !ft_strncmp(line + x, "-n", 2))
	{
		printf("\n\tsdfasf\n");
		new_line = 0;
		x += 3;
	}
	while (line[x])
	{
		if (line[x] == ' ')
		{
			write(1, &line[x], 1);
			x++;
			while (line[x] && line[x] == ' ')
				x++;
		}
		if (line[x] == 39)
		{
			// printf("\n\t39:%s\n", line + x);
			x++;
			while (line[x] && line[x] != 39)
			{
				write(1, &line[x], 1);
				x++;
			}
			x++;
		}
		if (line[x] == 34)
		{
			// printf("\n\t34:%s\n", line + x);
			x++;
			while (line[x] && line[x] != 34)
			{
				write(1, &line[x], 1);
				x++;
			}
			x++;
		}
		if (!line[x])
			break ;
		// printf("\nprinting: %c\t%d\n", line[x], line[x]);
		write(1, &line[x], 1);
		x++;
	}
	// printf("2 echosss: %s\n", line + x);
	// ft_write(line + x);
	if (new_line)
		ft_write("\n");

	(void)data;
}

void	ft_check_cmd(char *line, t_data *data)
{
	// printf("line: -%s-\n", line);		//		LE NODE->LINE SONO GIA' PULITE DEGLI SPAZI DAVANTI
//	int	len;

//	len = ft_strlen(line);
	//if (len == 4 && !ft_strncmp(line, "echo", 4))
//	printf("strncmp: %d\n", ft_strncmp(line, "echo ", 5));
	if (ft_strchr('|', line) != -1)
		ft_pipe(line, data);
	// else if(ft_strchr('>', line) != -1 || ft_strchr('<', line) != -1)
	// 	ft_redir(line,data);
	else if (!ft_strncmp(line, "echo ", 5) || ft_strncmp(line, "echo ", 5) == -32)
		ft_echo(line + 4, data);
	else if (!ft_strncmp(line, "cd ", 3) || ft_strncmp(line, "cd ", 3) == -32)
		ft_cd(line + 3, data);
	else if (!ft_strncmp(line, "pwd ", 4) || ft_strncmp(line, "pwd ", 4) == -32)
		ft_pwd(line + 3, data);
	else if (!ft_strncmp(line, "", 1))
		return ;
	else if (!ft_strncmp(line, "export ", 7) || ft_strncmp(line, "export ", 7) == -32)
		ft_export(line + 6, data);
	else if (!ft_strncmp(line, "env ", 4) || ft_strncmp(line, "env ", 4) == -32)
		ft_env(line + 3, data);
	else if (!ft_strncmp(line, "unset ", 6) || ft_strncmp(line, "unset ", 6) == -32)
		ft_unset(line + 5, data);
	else if (!ft_strncmp(line, "exit ", 5) || ft_strncmp(line, "exit ", 5) == -32)
		ft_exit("exit\n", data);
	else if (ft_check_execve(line,data))
		ft_do_execve(data);			//IMPORTANTE SE C'E' IL PUNTO e VIRGOLA 
									//HA IL RETURN 0=SUCCESS, 1=NOT SUCCESS
	else
	{
		ft_write("minishell: command not found\n");
		errno = 1;
	}
}

void	ft_exec_cmd(char *line, t_data *data)
{
	int	x;

//	 printf("0 line: %s\n", line);
	x = 0;

	data->std_fd[0] = dup(0);
	data->std_fd[1] = dup(1);
	// printf("line: %s/n", line);
	tcsetattr(0, 0, &data->old_term);
	while (ft_strchr('$', line + x) != -1)// && ft_strchr('\'', line) == -1)
		ft_env_line(&line, &x, data);
	
	//  printf("1 line: %s\n", line);
	if (ft_strchr('\'', line) || ft_strchr('\"', line))
		ft_clean_quotes(&line);
	
	if(ft_strchr('>', line) != -1 || ft_strchr('<', line) != -1)
		line = ft_redir(line,data);
	//   printf("2 line: %s\n", line);
	if (line)
		ft_check_cmd(line, data);
	
	free(line);

	dup2(data->std_fd[1],1);
	close(data->std_fd[1]);
	dup2(data->std_fd[0], 0);
	close(data->std_fd[0]);




	tcsetattr(0, 0, &data->my_term);


	// int x = 0;
	// while (data->envp[x])
	// {
	// 	printf("\t%s\n", data->envp[x++]);
	// }
}
