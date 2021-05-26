#include "my_minishell.h"

int	ft_check_double(t_read **head)
{
	t_read	*tmp;
	t_read	*tmp_x;
	int		num;

	tmp = *head;
	while (tmp)
	{
		num = tmp->pos;
		tmp_x = *head;
		while (tmp_x)
		{
			if (tmp_x->pos == num && ft_strcmp(tmp->line, tmp_x->line))
			{
				if (ft_strcmp(tmp->line, tmp_x->line) < 0)
					tmp_x->pos++;
				else
					tmp->pos++;
				return (1);
			}
			tmp_x = tmp_x->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_get_pos(t_read **head)
{
	t_read	*tmp;
	t_read	*tmp_x;
	int		num;

	tmp = *head;
	while (tmp)
	{
		num = tmp->line[0];
		tmp_x = *head;
		while (tmp_x)
		{
			if (tmp_x->line[0] > num)
				tmp_x->pos++;
			tmp_x = tmp_x->next;
		}
		tmp = tmp->next;
	}
	num = ft_check_double(head);
	while (num)
		num = ft_check_double(head);
}

void	ft_print_sort(t_read **head, t_data *data)
{
	t_read	*tmp;
	t_read	*tmp_x;
	int		len;

	tmp = *head;
	len = 1;
	ft_get_pos(head);
	tmp = *head;
	while (len <= data->env_len)
	{
		tmp_x = *head;
		while (tmp_x)
		{
			if (tmp_x->pos == len)
			{
				//printf("pos:%d\t\t%s\n", tmp_x->pos, tmp_x->line);
				ft_write(tmp_x->line);
				ft_write("\n");
				break ;
			}
			tmp_x = tmp_x->next;
		}
		tmp = tmp->next;
		len++;
	}

}