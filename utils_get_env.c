#include "my_minishell.h"
#include "my_minishell2.h"

char	*ft_itoa_errno(int num)
{
	char	*new;
	int		tmp;
	int		x;

	tmp = num;
	x = 3;
	// printf("num:%d\n", num);
//	printf("%s\n", var);
	while (tmp > 10)
	{
		tmp /= 10;
		x++;
	}
	// printf("%d\n", x);
//	x += ft_strlen(var);
	new = (char *)malloc(sizeof(char) * (x + 1));
	new[x--] = '\0';
	// while (var[--len] != '?')
	// 	new[x--] = var[len];
	while (num >= 10)
	{
		new[x--] = num % 10 + 48;
		num /= 10;
	}
	new[x--] = num + 48;
	// len -= 2;
	// while (x && var[--len])
	// 	new[x--] = var[len];
	while (x)
		new[x--] = ' ';
	// printf("new: %s\n", new);
	// free(var);
	return (new);
}

void	ft_list_to_matr(t_read **env_head, char ***envp, t_data *data)
{
	char	**new;
	t_read	*tmp;
	int		x;

	x = 0;
	tmp = *env_head;
	new = (char **)malloc(sizeof(char *) * (data->env_len + 1));
	while (tmp)
	{
		new[x] = tmp->line;//(*envp)[x];
		x++;
		tmp = tmp->next;
	}	
	new[x] = NULL;
//	*envp = NULL;
	free(*envp);
	*envp = new;
	// envp = &new;
}

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
	len = 0;
	while (tmp[len + x])
	{
		while (tmp[len + x] == ' ')
			len++;
		if (!tmp[len + x])
			break ;
		fixed[x] = tmp[len + x];
		x++;
	}
	fixed[x++] = '=';
	fixed[x++] = '\'';
	fixed[x++] = '\'';
	fixed[x] = '\0';
	// free(*line);
	// free(tmp);
	// *line = NULL;
	*line = fixed;
}

int	ft_search_env(char *line, int x, int len, t_data *data)
{
	t_read	*tmp;
	t_read	*tmp_x;

	tmp = *data->env_head;
	tmp_x = tmp;
	// printf("search: %s\t%d\n", line, len);
	if (len == -1)
		len = ft_strlen(line);
	if (!ft_strncmp(line, tmp->line, len) && !ft_strncmp(line, tmp->line, len + 1))
	{
		*data->env_head = (*data->env_head)->next;
		free(tmp->line);
		free(tmp);
		data->env_len--;
		return (1);
	}
	while (tmp)
	{
		tmp_x = tmp;
			// printf("\t%s\t%d\t%d\n", tmp->line, ft_strncmp(line, tmp->line, len), ft_strncmp(line, tmp->line, len + 1));
		tmp = tmp->next;
		if (tmp && !ft_strncmp(line, tmp->line, len) && (!ft_strncmp(line, tmp->line, len + 1) || ft_strncmp(line, tmp->line, len + 1) == -61))
		{
			tmp_x->next = tmp->next;
			free(tmp->line);
			free(tmp);
			data->env_len--;
			return (1);
		}
	}
	return (0);


	(void)x;
}

void	ft_add_env(char *line, int fix, t_data *data)
{
	t_read	*new;
	// int		fix;

	// printf("add_env:line: %d\n", line[ft_strchr('=', line) + 1]);
	// fix = 0;
	new = (t_read *)malloc(sizeof(t_read) * 1);
	// if (ft_strchr('=', line) < 0)
		// ft_fix_env(&line);
	// if (line[ft_strchr('=', line) + 1] == 39 && line[ft_strchr('=', line) + 2] == 39)
		// fix++;
	new->line = ft_strdup(line);
	new->next = NULL;
	ft_unset(line, data);
	if (fix)
	{
		free(line);
		// printf("fixed: %s\t%s\n", line, new->line);
	}
	// ft_search_env(line, 0, ft_strchr('=', line), data);
	ft_append_read(new, data->env_head);
	data->env_len++;
	ft_list_to_matr(data->env_head, &data->envp, data);
}
