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
	ret = chdir(line + x);
	if (ret == -1)
	{
		ft_write_2(strerror(errno));
		errno = 1;
		return ;
	}
	new = ft_strjoin("OLDPWD=", tmp);
	if (new)
		ft_add_env(new, 1, data);
	free(tmp);
	tmp = getcwd(NULL, 0);
	new = ft_strjoin("PWD=", tmp);
	ft_add_env(new, 1, data);
	free(tmp);
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
	while (line[x] == ' ')
		x++;
	if ((!ft_strncmp(line + x, "-n ", 3) || ft_strncmp(line + x, "-n ", 3) == -32) && !ft_strncmp(line + x, "-n", 2))
	{
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
		write(1, &line[x], 1);
		x++;
	}
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
		ft_exit_cmd(line + 4, data);
	else if (ft_check_execve(line,data))
		ft_do_execve(line, data);
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

		x = 0;
		tcsetattr(0, 0, &data->old_term);
		while (ft_strchr('$', line + x) != -1)
			ft_env_line(&line, &x, data);
		if (ft_strchr('\'', line) || ft_strchr('\"', line))
			ft_clean_quotes(&line);
		if(ft_strchr('>', line) != -1 || ft_strchr('<', line) != -1)
		{
			if (ft_redir(&line, data) == 0)
			{
				if (!errno || errno == 258)
				{
					ft_write_2("syntax error near unexpected token");
					errno = 258;
				}
				else
				{
					ft_write_2(strerror(errno));
					errno = 1;
				}
				x = 666;
			}
		}
		if (line && x != 666)
			ft_check_cmd(line, data);
		
		free(line);

		dup2(data->std_fd[1],1);
		dup2(data->std_fd[0], 0);
		x = errno;
		if (!stat("/tmp/minishell", &t_stat))					//METTERE ALLA FINE?		// modifica errno..
			unlink("/tmp/minishell");				
		errno = x;
	tcsetattr(0, 0, &data->my_term);
}
