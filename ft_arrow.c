#include "my_minishell.h"

void	ft_arrow_up(t_data *data, int x)
{
	t_read *tmp;

	if (!*data->cmd_head)
		return ;
	tmp = *data->cmd_head;
	printf("x: %d\n", x);
	//x--;
	while (tmp->next && x > 0)
	{
		tmp = tmp->next;
		x--;
	}
	printf("history: %s\n", tmp->line);
}
