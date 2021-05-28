#include "my_minishell.h"

int	ft_search_env(char *line, int len, t_data *data)
{
	t_read	*tmp;
	t_read	*tmp_x;

	tmp = *data->env_head;
	tmp_x = tmp;
	if (!ft_strncmp(line, tmp->line, len))
	{
		*data->env_head = (*data->env_head)->next;
		free(tmp);
		data->env_len--;
		return (1);
	}
	while (tmp)
	{
		tmp_x = tmp;
		tmp = tmp->next;
		if (tmp && !ft_strncmp(line, tmp->line, len))
		{
			tmp_x->next = tmp->next;
			free(tmp);
			data->env_len--;
			return (1);
		}
	}
	return (0);
}

void	ft_unset(char *line, t_data *data)				/// unset deve cercare fino all' '='
{
	int	len;
	int	x;

	len = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	while (line[x + len] && line[x + len] != ' ')
		len++;
	if (!line[x])
	{
		ft_write("not enough arguments\n");
		return ;
	}
	else
		ft_search_env(line + x, len, data);

}

void	ft_add_env(char *line, t_data *data)
{
	t_read	*new;

	new = (t_read *)malloc(sizeof(t_read) * 1);
	new->line = line;
	new->next = NULL;
	printf("ft_add_env - line: %s\n", line);
	ft_unset(line, data);
	ft_append_read(new, data->env_head);
	data->env_len++;
}

void	ft_env(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (!line[x] && line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_cmd(data->env_head);
}

void	ft_export(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (!line[x] && line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_sort(data->env_head, data);
	else
		ft_add_env(line, data);
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