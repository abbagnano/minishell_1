#include "my_minishell.h"

void	ft_cd(char *line, t_data *data)
{
	int		x;
	int		ret;
	char	*tmp;

	x = 0;
	if (!line[x])
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
	ft_update_pwd(tmp, data);
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

void	ft_echo(char *line)
{
	int	x;
	int	new_line;

	x = 0;
	new_line = 1;
	while (line[x] == ' ')
		x++;
	ft_option_echo(&new_line, &x, line);
	while (line[x])
	{
		ft_write_echo(&x, line);
		if (!line[x])
			break ;
		write(1, &line[x], 1);
		x++;
	}
	if (new_line)
		ft_write("\n");
	errno = 0;
}

void	ft_check_cmd(char *line, t_data *data)
{
	if (!ft_strncmp(line, "echo ", 5) || ft_strncmp(line, "echo ", 5) == -32)
		ft_echo(line + 4);
	else if (!ft_strncmp(line, "cd ", 3) || ft_strncmp(line, "cd ", 3) == -32)
		ft_cd(line + 2, data);
	else if (!ft_strncmp(line, "pwd ", 4) || ft_strncmp(line, "pwd ", 4) == -32)
		ft_pwd(line + 3, data);
	else if (!ft_strncmp(line, "export ", 7)
		|| ft_strncmp(line, "export ", 7) == -32)
		ft_export(line + 6, data);
	else if (!ft_strncmp(line, "env ", 4) || ft_strncmp(line, "env ", 4) == -32)
		ft_env(line + 3, data);
	else if (!ft_strncmp(line, "unset ", 6)
		|| ft_strncmp(line, "unset ", 6) == -32)
		ft_unset(line + 5, data);
	else if (!ft_strncmp(line, "exit ", 5)
		|| ft_strncmp(line, "exit ", 5) == -32)
		ft_exit_cmd(line + 4, data);
	else if (ft_check_execve(line, data))
		ft_do_execve(line, data);
	else
	{
		ft_write_2("minishell: command not found");
		errno = 127;
	}
}

void	ft_exec_cmd(char *line, t_data *data)
{
	int			x;
	struct stat	t_stat;

	x = 0;
	tcsetattr(0, 0, &data->old_term);
	while (ft_strchr('$', line + x) != -1)
		ft_env_line(&line, &x, data);
	if (ft_strchr('\'', line) || ft_strchr('\"', line))
		ft_clean_quotes(&line);
	if (ft_strchr('>', line) != -1 || ft_strchr('<', line) != -1)
	{
		if (ft_redir(&line, data) == 0)
			ft_error_redir(&x);
	}
	if (line && x != 666)
		ft_check_cmd(line, data);
	free(line);
	dup2(data->std_fd[1], 1);
	dup2(data->std_fd[0], 0);
	x = errno;
	if (!stat("/tmp/minishell", &t_stat))
		unlink("/tmp/minishell");
	errno = x;
	tcsetattr(0, 0, &data->my_term);
}
