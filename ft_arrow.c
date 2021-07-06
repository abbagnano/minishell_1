#include "my_minishell.h"
#include "my_minishell2.h"

void	ft_line_to_linod(t_char **line_head, char *line)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	ft_free_char(line_head);
	while (line[x])
	{
		ft_buffering(line[x], &y, line_head);
		x++;
	}
}

void	ft_arrow_up(t_char **line_head, t_data *data, int x, int *len)
{
	t_read	*tmp;

	if (!*data->cmd_head)
		return ;
	tmp = *data->cmd_head;
	while (tmp->next && x > 0)
	{
		tmp = tmp->next;
		x--;
	}
	ft_line_to_linod(line_head, tmp->line);
	ft_write(tgetstr("cr", NULL));
	ft_write(tgetstr("cd", NULL));
	ft_write("\033[0;32mminishell% \033[0m");
	if (x == -1)
	{
		*len = 0;
		ft_free_char(line_head);
		line_head = NULL;
		return ;
	}
	ft_write(tmp->line);
	*len = ft_strlen(tmp->line);
}
