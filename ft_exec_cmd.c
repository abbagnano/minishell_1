#include "my_minishell.h"

void	ft_cd(char *line, t_data *data)
{
	int	ret;

	if (ft_strncmp(line, "cd ", 3) == -32)		//se il comando è solo "cd" senza path allora non fa niente
		return ;
	ret = chdir(line);
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
	path = getcwd(path, 1);
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
	while (line[x] == ' ')
		x++;
	if (!ft_strncmp(line + x, "-n ", 3) || ft_strncmp(line + x, "-n ", 3) == -32)
	{
		new_line = 0;
		x += 3;
	}
	ft_write(line + x);
	if (new_line)
		ft_write("\n");

	(void)data;
}

void	ft_check_cmd(char *line, t_data *data)
{
	//printf("line: -%s-\t-%d-\n", line, (int)line);		//		LE NODE->LINE SONO GIA' PULITE DEGLI SPAZI DAVANTI
	int	len;

	len = ft_strlen(line);
	//if (len == 4 && !ft_strncmp(line, "echo", 4))
//	printf("strncmp: %d\n", ft_strncmp(line, "echo ", 5));
	if (!ft_strncmp(line, "echo ", 5) || ft_strncmp(line, "echo ", 5) == -32)
		ft_echo(line + 5, data);
	else if (!ft_strncmp(line, "cd ", 3) || ft_strncmp(line, "cd ", 3) == -32)
		ft_cd(line + 3, data);
	else if (!ft_strncmp(line, "pwd ", 4) || ft_strncmp(line, "pwd ", 4) == -32)
		ft_pwd(line + 4, data);
	else if (!ft_strncmp(line, "", 1))
		return ;
	else if (!ft_strncmp(line, "export ", 7) || ft_strncmp(line, "export ", 7) == -32)
		ft_export(line + 7, data);
	else if (!ft_strncmp(line, "env ", 4) || ft_strncmp(line, "env ", 4) == -32)
		ft_env(line + 4, data);
	else if (!ft_strncmp(line, "unset ", 6) || ft_strncmp(line, "unset ", 6) == -32)
		ft_unset(line + 6, data);
	else if (!ft_strncmp(line, "exit ", 5) || ft_strncmp(line, "exit ", 5) == -32)
		ft_exit("exit\n", data);
	else
		ft_write("minishell: command not found\n");
}

void	ft_exec_cmd(t_data *data)
{
	t_read	*tmp;
	//int		len;

	while (*data->cmd_head)
	{
		//len = ft_strchr('\n', line);
		ft_check_cmd((*data->cmd_head)->line, data);
		tmp = (*data->cmd_head);
		*data->cmd_head = (*data->cmd_head)->next;
		free(tmp);
	}
}