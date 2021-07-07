#include "my_minishell.h"

void	ft_init_term(t_data *data)
{
	data->std_fd[0] = dup(0);
	data->std_fd[1] = dup(1);
	tgetent(NULL, getenv ("TERM"));
	tcgetattr(0, &data->old_term);
	tcgetattr(0, &data->my_term);
	data->my_term.c_lflag &= ~(ICANON | ECHO);
	data->my_term.c_cc[VINTR] = 0;
	data->my_term.c_cc[VQUIT] = 0;
	tcsetattr(0, 0, &data->my_term);
}

void	ft_no_arg(t_data *data)
{
	t_char	*line_head;
	t_read	*cmd;

	line_head = NULL;
	cmd = NULL;
	ft_write("\033[0;32mminishell% \033[0m");
	ft_read_ops(line_head, cmd, data);
	ft_write("exit\n");
}

void	ft_arg(char *av, t_data *data, char **env)
{
	char	*command[2];

	(command)[0] = av;
	(command)[1] = NULL;
	execve((command)[0], command, env);
	ft_write_2(strerror(errno));
	ft_exit_num(2, data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	data.cmd_head = (t_read **)malloc(sizeof(t_read *) * 1);
	*data.cmd_head = NULL;
	data.env_head = (t_read **)malloc(sizeof(t_read *) * 1);
	*data.env_head = NULL;
	ft_init_term(&data);
	ft_get_env(env, &data);
	if (ac == 1)
		ft_no_arg(&data);
	if (ac >= 2)
		ft_arg(av[1], &data, env);
	ft_exit("", &data);
}
