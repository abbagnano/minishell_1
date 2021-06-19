#include "my_minishell.h"

int		ft_check_quote(char	*line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'')
		{
			x++;
			while (line[x] && line[x] != '\'')
				x++;
			if (!line[x])
				return (0);
			else if (line[x] == '\'')
				x++;
		}
		else if (line[x] == '\"')
		{
			x++;
			while (line[x] && line[x] != '\"')
				x++;
			if (!line[x])
				return (0);
			else if (line[x] == '\"')
				x++;
		}		
		x++;
	}
	return (1);
}


void	ft_clean_line_39(char **line, int *x)
{
	int		len;
	int		z;
	char	*new;
	char	*tmp;

	len = ft_strlen(*line);
	new = (char *)malloc(sizeof(char) * (len - 2));
	z = 0;
	len = 0;
	tmp = *line;
	while (tmp[len + z] && tmp[len + z] != 39 && len < 2)
	{
		new[z] = tmp[len + z];
		z++;
		if (tmp[len + z] == 39)
			len++;
	}
	*x = z;//len + z - 2;
	// printf("x: %d\n", *x);
	while (tmp[len + z])
	{
		new[z] = tmp[len + z];
		z++;
	}
	new[z] = '\0';
	free(*line);
	*line = new;
	// printf("\t\tclean_39\t%s\n", *line);
}

void	ft_clean_line_34(char **line, int *x)
{
	int		len;
	int		z;
	char	*new;
	char	*tmp;

	len = ft_strlen(*line);
	new = (char *)malloc(sizeof(char) * (len - 2));
	z = 0;
	len = 0;
	tmp = *line;
	// while (tmp[len + z] && z < *x)
	// {
	// 	new[z] = tmp[len + z];
	// 	z++;
	// }
	while (tmp[len + z] && tmp[len + z] != 34 && len < 2)
	{
		new[z] = tmp[len + z];
		z++;
		if (tmp[len +z] == 39)
		{

		}
		if (tmp[len + z] == 34)
			len++;
	}
	*x = z - 1;//len + z - 2;
//	printf("x: %d\n", *x);
	while (tmp[len + z])
	{
		new[z] = tmp[len + z];
		z++;
	}
	new[z] = '\0';
	free(*line);
	*line = new;
	// printf("\t\tclean_34\t%s\n", *line);
}

void	ft_clean_clean(char **line, int e, int s)
{
	char	*new;
	int		x;
	int		y;

	new = (char *)malloc(sizeof(char) * (ft_strlen(*line) - 2));
	x = 0;
	y = 0;
	while ((*line)[x + y])
	{
		if (x + y == e || x + y == s)
			y++;
		new[x] = (*line)[x + y];
		x++;
	}
	new[x] = '\0';
	free(*line);
	*line = new;

}

int		ft_check_clean(char **line, int *x, char c)
{
	int	z;
	int s;
	int e;

	z = *x;
	s = z;
	while ((*line)[z])
	{
		// printf("\tcheck:%s	\n",(*line + z));
		z++;
		if ((*line)[z] && c == 39 && ((*line)[z] == '$' || (*line)[z] == '\"'))
		{
			while ((*line)[z] && (*line)[z] != c)
				z++;
			*x = z;// + 1;
			return (0);
		}
		else if ((*line)[z] && c == 34 && (*line)[z] == '\'')
		{
			while ((*line)[z] && (*line)[z] != c)
				z++;
			*x = z;// + 1;
			return (0);
		}
		else if ((*line)[z] && ((*line)[z] == '>' || (*line)[z] == '<' || (*line)[z] == ' '))
		{
			while ((*line)[z] && (*line)[z] != c)
				z++;
			*x = z;// + 1;
			return (0);
		}
		else if ((*line)[z] && (*line)[z] == c)
		{
			*x = z;
			e = z;
			ft_clean_clean(line, s, e);
			// if (c == 39)
			// 	ft_clean_line_39(line, &z);
			// else
			// 	ft_clean_line_34(line, x);
			return (1);
		}
	}
	return (0);
}

void	ft_clean_quotes(char **line)
{
	int		x;
	// char	*tmp;

	x = 0;
	// tmp = *line;
	while ((*line)[x])
	{	
		// printf("(*line):-%s-\n", (*line + x));
		if ((*line)[x] == 39)
			ft_check_clean(line, &x, 39);
		else if ((*line)[x] == '\"')
			ft_check_clean(line, &x, '\"');
	//	 printf("tmp_x: %d\n", x);
		x++;
	}
	printf("%s\n", *line);
}



// int		ft_check_quotes(t_char **line_head)
// {
// 	t_char	*tmp;
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	tmp = *line_head;
// 	while (tmp)
// 	{
// 		if (tmp->buf == '\'')
// 			y++;
// 		else if (tmp->buf == '\"')
// 			x++;
// 		tmp = tmp->next;
// 	}
// 	if (y % 2 || x % 2)
// 		return (0);
// 	return (1);
// }


// int		ft_check_quotes_clean(t_char **line_head, char c)
// {
// 	t_char	*tmp;

// 	tmp = *line_head;
// //	printf("asdasd\n");
// 	while (tmp)
// 	{
// 		while (tmp && tmp->buf == ' ')
// 			tmp = tmp->next;
// 		if (tmp && (tmp->buf == '>' || tmp->buf == '<'))
// 			return (0);
// 		else if (tmp && tmp->buf == c)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }