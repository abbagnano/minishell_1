#include "my_minishell.h"

void	ft_env(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_cmd(data->env_head);
}

void	ft_export(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_sort(data->env_head, data);
}

void	ft_get_env(char **env, t_data *data)
{
	int		x;
	t_read	*new;

	x = 0;
	while (env[x])
	{
		new = (t_read *)malloc(sizeof(t_read) * 1);
		new->line = env[x];
		new->pos = 1;
		new->next = NULL;
		ft_append_read(new, data->env_head);
		x++;
	}
	data->env_len = x; 
	//ft_print_cmd(data->env_head);
}