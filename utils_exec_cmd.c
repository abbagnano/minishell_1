#include "my_minishell.h"
#include "my_minishell2.h"

void	ft_update_pwd(char *tmp, t_data *data)
{
	char	*new;

	new = ft_strjoin("OLDPWD=", tmp);
	if (new)
		ft_add_env(new, 1, data);
	free(tmp);
	tmp = getcwd(NULL, 0);
	new = ft_strjoin("PWD=", tmp);
	ft_add_env(new, 1, data);
	free(tmp);
}

void	ft_option_echo(int *new_line, int *x, char *line)
{
	if ((!ft_strncmp(line + *x, "-n ", 3)
			|| ft_strncmp(line + *x, "-n ", 3) == -32)
		&& !ft_strncmp(line + *x, "-n", 2))
	{
		*new_line = 0;
		*x += 3;
	}
	while (line[*x] == ' ')
		(*x)++;
	if (line[*x] == '-' && line[*x + 1] == 'n')
		ft_option_echo(new_line, x, line);
}

void	ft_write_echo(int *x, char *line)
{
	if (line[*x] == ' ' && line[*x + 1])
	{
		if (!ft_last_spaces(line + *x))
			write(1, &line[*x], 1);
		(*x)++;
	}
	while (line[*x] && line[*x] == ' ')
		(*x)++;
	if (line[*x] == 39)
	{
		(*x)++;
		while (line[*x] && line[*x] != 39)
		{
			write(1, &line[*x], 1);
			(*x)++;
		}
		(*x)++;
	}
	if (line[*x] == 34)
	{
		(*x)++;
		while (line[*x] && line[*x] != 34)
		{
			write(1, &line[*x], 1);
			(*x)++;
		}
		(*x)++;
	}
}

void	ft_error_redir(int *x)
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
	*x = 666;
}
