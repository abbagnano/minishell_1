#include "my_minishell.h"

void	ft_print_env(t_read **head)
{
	t_read *tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strstr("=''", tmp->line))
		{	
			ft_write(tmp->line);
			ft_write("\n");
		}
		tmp = tmp->next;
	}
}

void	ft_unset(char *line, t_data *data)				/// unset deve cercare fino all' '='
{
	int	len;
	int	x;

	len = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	while (line[x + len] && (line[x + len] != ' ' && line[x + len] != '='))
		len++;
	if (line[x + len] == '=')
		len++;
	if (!line[x])
	{
		ft_write("not enough arguments\n");
		return ;
	}
	else
		ft_search_env(line + x, x, len, data);

}

void	ft_env(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_env(data->env_head);
	else
		ft_write("bad option or too many arguments\n");
}

void	ft_export(char *line, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (!line[x])
		ft_print_sort(data->env_head, data);
	else
		ft_add_env(line + x, data);
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