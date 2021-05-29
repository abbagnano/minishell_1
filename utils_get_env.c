#include "my_minishell.h"

void	ft_fix_env(char **line)
{
	int		x;
	int		len;
	char	*fixed;
	char	*tmp;

	x = 0;
	len = ft_strlen(*line);
	fixed = (char *)malloc(sizeof(char) * (len + 4));
	tmp = *line;
	while (tmp[x])
	{
		fixed[x] = tmp[x];
		x++;
	}
	fixed[x++] = '=';
	fixed[x++] = '\'';
	fixed[x++] = '\'';
	fixed[x] = '\0';
	*line = fixed;
}

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

void	ft_add_env(char *line, t_data *data)
{
	t_read	*new;

	new = (t_read *)malloc(sizeof(t_read) * 1);
	if (ft_strchr('=', line) < 0)
		ft_fix_env(&line);
	new->line = line;
	new->next = NULL;
	ft_unset(line, data);
	ft_append_read(new, data->env_head);
	data->env_len++;
}
