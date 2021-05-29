#include "my_minishell.h"

void	ft_print_cmd(t_read **head)
{
	t_read *tmp;

	tmp = *head;
	while (tmp)
	{
		//printf("%s\n", tmp->line);
		ft_write(tmp->line);
		ft_write("\n");
		tmp = tmp->next;
	}
}

void	ft_no_arg(t_data *data)
{
	ft_write("\033[0;32mminishell% \033[0m");
	ft_read_ops(data);
	ft_write("exit\n");
	ft_print_cmd(data->cmd_head);
}


int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.cmd_head = (t_read **)malloc(sizeof(t_read *) * 1);
	*data.cmd_head = NULL;
	data.env_head = (t_read **)malloc(sizeof(t_read *) * 1);
	*data.env_head = NULL;
	ft_get_env(env, &data);	
	if (ac == 1)
		ft_no_arg(&data);
	(void)av;
	ft_exit("", &data);
}