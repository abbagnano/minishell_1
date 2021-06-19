#include "my_minishell.h"

void	ft_get_var(char **var, int *len, t_data *data)
{
	t_read	*tmp;

	tmp = *data->env_head;
	while (tmp && (*var)[1] != '?' && ft_strncmp((*var + 1), tmp->line, *len) != -61)
		tmp = tmp->next;
	if ((*var)[1] == '?')
	{
		free(*var);
		*var = ft_itoa_errno(errno, *len);//(errno);
		// printf("-%s-\n", *var);
		*len = 2;
	}
	else
	{
		free(*var);
		// *var = NULL;
		*var = "\0";
		if (tmp)
			*var = tmp->line;
	}
}

void	ft_var_line(char *var, char **line, int x, t_data *data)
{
	char	*tmp;
	char	*new;
	int		tot;
	int		z;
	int 	len;

	len = ft_strlen(var);
	ft_get_var(&var, &len, data);
	// printf("len:%d\tvar: %s\n",len, var);
	tot = ft_strlen(*line) - len + ft_strlen(var + len);
	new = (char *)malloc(sizeof(char) * (tot + 1));
	tmp = *line;
	z = 0;
	while (z < x)//(tmp[z] != '$')
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
	// *line = NULL;
	if (!ft_strncmp(var, "$ 0", 3))
		free(var);
	*line = new;
//	printf("vvar:%s\n", *line);
//	ft_check_cmd(new, data);
//	free(new);
}


// void	ft_var_line(char *var, char **line, int len, t_data *data)
// {
// 	char	*tmp;
// 	char	*new;
// 	int		tot;
// 	int		z;

// 	ft_get_var(&var, &len, data);
// //	printf("len:%d\tvar: %s\n",len, var);
// 	tot = ft_strlen(*line) - len + ft_strlen(var + len);
// 	new = (char *)malloc(sizeof(char) * (tot + 1));
// 	tmp = *line;
// 	z = 0;
// 	while (tmp[z] != '$')
// 	{
// 		new[z] = tmp[z];
// 		z++;
// 	}
// 	tot = z;
// 	z = 0;
// 	while (var[len + z])
// 	{
// 		new[tot + z] = var[len + z];
// 		z++;
// 	}
// 	len += tot;
// 	tot += z;
// 	z = 0;
// 	while (tmp[len + z])
// 	{
// 		new[tot + z] = tmp[len + z];
// 		z++;
// 	}
// 	new[tot + z] = '\0';
// 	free(*line);
// 	*line = new;
// //	printf("vvar:%s\n", *line);
// //	ft_check_cmd(new, data);
// //	free(new);
// }



/////				SISTEMARE "$PATH" '$TERM' ... IL PRIMO DEVE FARLO E IL SECONDO NO


void	ft_env_line(char **line, int *x, t_data *data)
{
	char	*tmp;
	char	*var;
	int		z;
	int		len;

	// z = *x;
	len = 0;
	tmp = *line;
	//  printf("line_env: %s\n", *line + z);
	// while (tmp[z] && tmp[z] != '$')
	// {
	// 	if (tmp[z] == '\"')
	// 	{
	// 		z++;
	// 		while (tmp[z] != '\"' && tmp[z + 1] != '$')
	// 			z++;
	// 	}
	// 	else if (tmp[z] == '\'')
	// 	{
	// 		z = ft_strchr('\'', tmp + z + 1);
	// 		*x += z;
	// 		 return ;
	// 		// if (ft_strchr('\'', tmp + z + 1) != -1)
	// 		// {
	// 		// 	ft_check_clean(tmp + z, z, '\'');
	// 		// 	(*x)++;
	// 		// 	return ;
	// 		// }
	// 	}
	// 	z++;
	// 	printf("\t\t%s\n", tmp + z);
	// }
	z = 0;
	// printf("pre x:%d\t%s\n", *x, *line + *x);
	*x += ft_strchr('$', (*line + *x));
	if (*x < 0)
		return ;
	// printf(" x:%d\t%s\n", *x, *line + *x);
	while (z < *x && tmp[z])
	{
		if (tmp[z] == 34)
		{
			// printf(" qwe\n");
			z++;
			while (z < *x && tmp[z] && tmp[z] != 34)
				z++;
			if (tmp[z] == 34)
				z++;
			continue ;
		}	
		else if (tmp[z] == 39)
		{
			// printf(" rty\n");
			z++;
			while (tmp[z] && tmp[z] != '\'')
				z++;
			if (z >= *x)
			{
				*x = z + 1;
				return ;
			}
		}
		z++;
	}
	while (z < *x && tmp[z])
		z++;
//	len = 0;
// printf("%s\n", tmp + z + len);
	while (tmp[z + len] && tmp[z + len] != ' ')// && tmp[z + len] != '\'' && tmp[z + len] != '\"')
	{
		len++;
		if (tmp[z + len] == '$' || tmp[z + len] == '?' || tmp[z + len] == '\'' || tmp[z + len] == '\"')
			break ;
	}
	if (tmp[z + len] == '?')
		len++;
	var = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (tmp[z + len] && tmp[z + len] != ' ')// && tmp[z + len] != '?')
	{
		var[len] = tmp[z + len];
		len++;
		if (tmp[z + len] == '$' || tmp[z + len] == '?' || tmp[z + len] == '\'' || tmp[z + len] == '\"')
			break ;
	}
	if (tmp[z + len] == '?')
	{
		var[len] = tmp[z + len];
		len++;
	}
	var[len] = '\0';
	//  printf("var: %s\n", var);
	ft_var_line(var, line, *x, data);
	// ft_var_line(var, line, len, data);
	// free(var);
	//
	//  printf("updated_line: %s\n", *line);
}