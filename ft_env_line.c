#include "my_minishell.h"

void	ft_get_var(char **var, int len, t_data *data)
{
	t_read	*tmp;

	tmp = *data->env_head;
	while (tmp && (*var)[1] != '?' && ft_strncmp((*var + 1), tmp->line, len) != -61)
		tmp = tmp->next;
	if ((*var)[1] == '?')
	{
		free(*var);
		*var = ft_itoa_errno(errno, len, *var);//(errno);
		len = 2;
	}
	else
	{
		free(*var);
		*var = "\0";
		if (tmp)
			*var = tmp->line;
	}
}

void	ft_var_line(char *var, char **line, int len, t_data *data)
{
	char	*tmp;
	char	*new;
	int		tot;
	int		z;

	ft_get_var(&var, len, data);
//	printf(" %s\n", var);
	tot = ft_strlen(*line) - len + ft_strlen(var + len);
	new = (char *)malloc(sizeof(char) * (tot + 1));
	tmp = *line;
	z = 0;
	while (tmp[z] != '$')
	{
		new[z] = tmp[z];
		z++;
	}
	tot = z;
	z = 0;
	while (var[len + z])
	{
		new[tot + z] = var[len + z];
		z++;
	}
	len += tot;
	tot += z;
	z = 0;
	while (tmp[len + z])
	{
		new[tot + z] = tmp[len + z];
		z++;
	}
	new[tot + z] = '\0';
	free(*line);
	*line = new;
//	printf("vvar:%p\n", *line);
//	ft_check_cmd(new, data);
//	free(new);
}

void	ft_env_line(char **line, t_data *data)
{
	char	*tmp;
	char	*var;
	int		x;
	int		len;

	x = 0;
	len = 0;
	tmp = *line;
	// printf("line: %s\n", line);
	while (tmp[x] && tmp[x] != '$')
		x++;
	while (tmp[x + len] && tmp[x + len] != ' ')
		len++;
	var = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (tmp[x + len] && tmp[x + len] != ' ')
	{
		var[len] = tmp[x + len];
		len++;
	}
	var[len] = '\0';
	ft_var_line(var, line, len, data);
//	free(var);
	// printf("var: %s\n", var);
	// printf("line: %s\n", line);
}