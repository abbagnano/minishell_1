#include "my_minishell.h"
#include "my_minishell2.h"

void	ft_cd(char *line, t_data *data)
{
	int		ret;
	int		x;
	char	*tmp;
	char	*new;

	x = 0;
	if (!line[x])		//se il comando è solo "cd" senza path allora non fa niente
		return ;
	while (line[x] == ' ')
		x++;
	if (ft_strchr('\'', line) == -1 || ft_strchr('\"', line) == -1)
	{
		ret = ft_strlen(line) - 1;
		while (line[ret] == ' ')
			ret--;
		line[ret + 1] = '\0';
	}
	tmp = getcwd(NULL, 0);
	// printf("-%s-\n", line + x);
	ret = chdir(line + x);
	if (ret == -1)
	{
		// 	char *asd = strerror(errno);
		// write(2, asd, strlen(asd));
		// printf("errno:%d\n", errno);
		ft_write_2(strerror(errno));
		// ft_write_2("\n");
		// perror(line + x);
		errno = 1;
		return ;
	}
	// free(tmp);
	new = ft_strjoin("OLDPWD=", tmp);
	// printf("%s\n", new);
	if (new)
		ft_add_env(new, 1, data);
	free(tmp);
	tmp = getcwd(NULL, 0);
	new = ft_strjoin("PWD=", tmp);
	ft_add_env(new, 1, data);
	free(tmp);

	///		aggiornare env $PWD & $OLDPWD ??
	// (void)data;
}

void	ft_pwd(char *line, t_data *data)
{
	char	*path;
	int		x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (line[x] && line[x] == '-')
	{
		ft_write_2("invalid option");
		errno = 1;
		return ;
	}
	path = NULL;
	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_write_2(strerror(errno));
		// ft_write("\n");
		// perror(path);
		errno = 1;
		return ;
	}
	ft_write(path);
	ft_write("\n");
	free(path);
	(void)data;
}

int	ft_last_spaces(char *str)
{
	int	x;

	x  = 0;
	while (str[x] && str[x] == ' ')
		x++;
	if (str[x])
		return (0);
	return (1);
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
		// printf("\n\tsdfasf\n");
		new_line = 0;
		x += 3;
	}
	while (line[x] == ' ')
		x++;
	while (line[x])
	{
		if (line[x] == ' ' && line[x + 1])
		{
			if (!ft_last_spaces(line + x))
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
	errno = 0;
	(void)data;
}

void	ft_exit_cmd(char *line, t_data *data)
{
	int	x;
	int	tot;

	x = 0;
	tot = 0;
	ft_write("exit\n");
	while (line[x] && line [x] == ' ')
		x++;
	while (line[x] && line[x] >= '0' && line[x] <= '9')
		tot = tot * 10 + line[x++] - 48;
	if (line[x] && line[x] != ' ' && (line[x] < '0' || line[x] > '9'))
	{
		ft_write_2("minishell: exit: numeric argument required");
		errno = 255;
		ft_exit_num(errno, data);
	}
	while (line[x] && line [x] == ' ')
		x++;
	if (line[x])
	{
		ft_write_2("minishell: exit: too many arguments");
		errno = 1;
		return ;
	}
	if (errno != 255)
		errno = tot;
	ft_exit_num(errno, data);
}

void	ft_check_cmd(char *line, t_data *data)
{
	// printf("line: -%s-\n", line);		//		LE NODE->LINE SONO GIA' PULITE DEGLI SPAZI DAVANTI
//	int	len;

//	len = ft_strlen(line);
	//if (len == 4 && !ft_strncmp(line, "echo", 4))
//	printf("strncmp: %d\n", ft_strncmp(line, "echo ", 5));
	// if (ft_strchr('|', line) != -1)
	// 	ft_pipe(line, data);
	// else if(ft_strchr('>', line) != -1 || ft_strchr('<', line) != -1)
	// 	ft_redir(line,data);
	// else 
	if (!ft_strncmp(line, "echo ", 5) || ft_strncmp(line, "echo ", 5) == -32)
		ft_echo(line + 4, data);
	else if (!ft_strncmp(line, "cd ", 3) || ft_strncmp(line, "cd ", 3) == -32)
		ft_cd(line + 2, data);
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
		ft_exit_cmd(line + 4, data);	// ft_exit("exit\n", data);
	else if (ft_check_execve(line,data))
		ft_do_execve(line, data);			//IMPORTANTE SE C'E' IL PUNTO e VIRGOLA 
									//HA IL RETURN 0=SUCCESS, 1=NOT SUCCESS
	else
	{
		ft_write_2("minishell: command not found");
		// ft_write(line);
		errno = 127;
		// exit(0);
	}
}

void	ft_exec_cmd(char *line, t_data *data)
{
	int	x;
	struct stat t_stat;

//	 printf("0 line: %s\n", line);
		x = 0;

		// data->std_fd[0] = dup(0);
		// data->std_fd[1] = dup(1);
		// printf("line: %s/n", line);
		tcsetattr(0, 0, &data->old_term);
		// printf("\t1 errno: %d\n", errno);
		while (ft_strchr('$', line + x) != -1)// && ft_strchr('\'', line) == -1)
			ft_env_line(&line, &x, data);
		// printf("\t1 errno: %d\n", errno);
		//  printf("1 line: %s\n", line);
		if (ft_strchr('\'', line) || ft_strchr('\"', line))
			ft_clean_quotes(&line);
		
		if(ft_strchr('>', line) != -1 || ft_strchr('<', line) != -1)
		{
			if (ft_redir(&line, data) == 0)
			{
				printf("Error REDIR\n");     //TEMPORANEO
				exit(0);
			}
		}
		// printf("x:%d\n", x);
		//   printf("2 line: %s\n", line);
		if (line)
			ft_check_cmd(line, data);
		
		free(line);

		dup2(data->std_fd[1],1);
		// close(data->std_fd[1]);
		dup2(data->std_fd[0], 0);
		// close(data->std_fd[0]);
		// printf("\t3 errno: %d\n", errno);
		x = errno;
		if (!stat("/tmp/minishell", &t_stat))					//METTERE ALLA FINE?		// modifica errno..
			unlink("/tmp/minishell");				
		errno = x;
		// printf("\t4 errno: %d\n", errno);
	tcsetattr(0, 0, &data->my_term);


	// int x = 0;
	// while (data->envp[x])
	// {
	// 	printf("\t%s\n", data->envp[x++]);
	// }
}
