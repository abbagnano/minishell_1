#include "my_minishell.h"

void	ft_free_env_read(t_read **head)
{
	t_read	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

void	ft_free_read(t_read **head)
{
	t_read	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
}

void	ft_exit(char *str, t_data *data)
{
	ft_write(str);
	if (*data->cmd_head)
		ft_free_read(data->cmd_head);
	free(data->cmd_head);
	if (*data->env_head)
		ft_free_read(data->env_head);
	//	ft_free_env_read(data->env_head);
	free(data->env_head);
	free(data->envp);
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	tcsetattr(0, 0, &data->old_term);
	// printf("xxxxxxxxxxx\n");
	// printf("waiting_leaks\n");
	// read(0, &str, 1);
	exit(0);
}
