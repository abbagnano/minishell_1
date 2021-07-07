#include "my_minishell.h"

void	ft_write_2(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	write(2, "\n", 1);
}

void	ft_exit_error(t_data *data)
{
	ft_write_2("minishell: exit: numeric argument required");
	errno = 255;
	ft_exit_num(errno, data);
}

int	ft_free_env(t_read	*tmp, t_data *data)
{
	free(tmp->line);
	free(tmp);
	data->env_len--;
	return (1);
}
