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

int		ft_check_clean(char *line, int *x, char c)
{
	int	z;

	z = 1;
	while (line[z])
	{
		if (line[z] && c == 39 && line[z] == '$')
		{
			while (line[z] && line[z] != c)
				z++;
			*x += z + 1;
			return (0);
		}
		else if (line[z] && (line[z] == '>' || line[z] == '<' || line[z] == ' '))
		{
			while (line[z] && line[z] != c)
				z++;
			*x += z + 1;
			return (0);
		}
		else if (line[z] && line[z] == c)
		{
			//*x += z + 1;
			return (1);
		}
		z++;
	printf("check:%s\n",line + z);
	}
	return (0);
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
	while (tmp[len + z] && tmp[len + z] != 39)
	{
		new[z] = tmp[len + z];
		z++;
		if (tmp[len + z] == 39)
			len++;
	}
	*x = len + z	;
	printf("x: %d\n", *x);
	while (tmp[len + z])
	{
		new[z] = tmp[len + z];
		z++;
	}
	new[z] = '\0';
	free(*line);
	*line = new;
//	printf("\tclean_39\t%s\n", *line);
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
	while (tmp[len + z] && tmp[len + z] != 34 && len < 2)
	{
		new[z] = tmp[len + z];
		z++;
		if (tmp[len + z] == 34)
			len++;
	}
	*x = len + z;
	printf("x: %d\n", *x);
	while (tmp[len + z])
	{
		new[z] = tmp[len + z];
		z++;
	}
	new[z] = '\0';
	free(*line);
	*line = new;
	printf("\tclean_34\t%s\n", *line);
}

void	ft_clean_quotes(char **line)
{
	int		x;
	char	*tmp;

	x = 0;
	tmp = *line;
	while (tmp[x])
	{	
		if (tmp[x] == '\'')
		{
			if (ft_check_clean(tmp + x, &x, '\''))
				ft_clean_line_39(line, &x);
		}
		else if (tmp[x] == '\"')
		{
			if (ft_check_clean(tmp + x, &x, '\"'))
				ft_clean_line_34(line, &x);
		}
		printf("tmp: %s\n", tmp + x);
		printf("tmp_x: %d\n", x);
		x++;
	}
	printf("end:%s\n", *line);
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