#include "my_minishell.h"

void	ft_print_cmd(t_read **head)
{
	t_read *tmp;

	tmp = *head;
	printf("printf..\n");
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
	//ft_print_cmd(data->cmd_head);
}

int		ft_matrlen(char **matr)
{
	int	x;

	x = 0;
	while (matr[x])
		x++;
	return (x);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

//	data.line_head = (t_char **)malloc(sizeof(t_char *) * 1);
//	*data.line_head = NULL;
	data.cmd_head = (t_read **)malloc(sizeof(t_read *) * 1);
	*data.cmd_head = NULL;
	data.env_head = (t_read **)malloc(sizeof(t_read *) * 1);
	*data.env_head = NULL;
	// data.envp = env;
	// ft_env(&data, env);
	ft_init_term(&data);
	ft_get_env(env, &data);	
	if (ac == 1)
		ft_no_arg(&data);
	(void)av;
	ft_exit("", &data);
}
