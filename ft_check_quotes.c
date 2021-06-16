#include "my_minishell.h"

int		ft_check_quotes(char *line, char c)
{
	int	x;
	int	z;

	x = 0;
	z = 0;
	while (line[z])
	{
		if (line[z]== c)
			x++;
		z++;
	}
	if (x % 2)
		return (0);
	return (1);
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