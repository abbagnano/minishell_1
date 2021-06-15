#include "my_minishell.h"

void	ft_var_line(char *var, char *line, int len, t_data *data)
{
	char	*new;
	int		tot;
	int		z;
	t_read	*tmp;

	// printf("var:%s\n", var);
	tmp = *data->env_head;
	while (tmp && ft_strncmp(var + 1, tmp->line, len) != -61)//'=')// && !ft_strncmp(var + 1, tmp->line, len - 1))
	{
	//	 printf("env: %s\n", tmp->line);
	//	 printf("cmp1: %d\tcmp2: %d\n", ft_strncmp(var + 1, tmp->line, len), ft_strncmp(var + 1, tmp->line, len));
		tmp = tmp->next;
	}
	free(var);
	var = "\0";
	if (tmp)
		var = tmp->line;
//	printf("var:%s\n", var);
	tot = ft_strlen(line) - len + ft_strlen(var + 5);
	new = (char *)malloc(sizeof(char) * (tot + 1));
	z = 0;
	while (line[z] != '$')
	{
		new[z] = line[z];
		z++;
	}
	tot = z;
	z = 0;
	while (var[z + len])
	{
		new[tot + z] = var[z + len];
		z++;
	}
	len += tot;
	tot += z;
	z = 0;
	while (line[tot + len + z])
	{
		new[tot + z] = line[len + z];
		z++;
	}
	new[tot + z + len] = '\0';
	// printf("len:%d\n", len);
//	printf("new: %s\n", new);
	ft_check_cmd(new, data);
	free(new);
}

void	ft_env_line(char *line, t_data *data)
{
	char	*var;
	int		x;
	int		len;

	x = 0;
	len = 0;
	// printf("line: %s\n", line);
	while (line[x] && line[x] != '$')
		x++;
	while (line[x + len] && line[x + len] != ' ')
		len++;
	var = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (line[x + len] && line[x + len] != ' ')
	{
		var[len] = line[x + len];
		len++;
	}
	var[len] = '\0';
	ft_var_line(var, line, len, data);
//	free(var);
	// printf("var: %s\n", var);
	// printf("line: %s\n", line);
}