/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:37:34 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/13 10:54:36 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_list_find_index_node_by_data(t_list **begin, void *data)
{
	int		index;
	t_list	*temp;

	if (!begin || !*begin || !data)
		return (-1);
	index = 0;
	temp = *begin;
	while (temp)
	{
		if (*(int *)temp->data == *(int *)data)
			return (index);
		index++;
		temp = temp->next;
	}
	return (-1);
}

int	ft_list_find_index_node_by_node(t_list **begin, t_list *node)
{
	int		index;
	t_list	*temp;

	if (!begin || !*begin || !node)
		return (-1);
	index = 0;
	temp = *begin;
	while (temp)
	{
		if (temp == node)
			return (index);
		index++;
		temp = temp->next;
	}
	return (-1);
}

void	ft_list_find_data_min_max_med(t_list **begin, int *min,
													int *max, int *med)
{
	t_list	*temp;
	int		i;
	int		size_list;

	if (!begin || !*begin)
		return ;
	*min = LIMIT_UP_INT;
	*max = LIMIT_DOWN_INT;
	temp = *begin;
	*med = 0;
	i = 0;
	size_list = ft_list_size_list(begin);
	while (temp)
	{
		i = ft_check_pos(begin, (*(int *)temp->data));
		if (i == size_list / 2)
			*med = (*(int *)temp->data);
		if ((*(int *)temp->data) < *min)
			*min = (*(int *)temp->data);
		if ((*(int *)temp->data) > *max)
			*max = (*(int *)temp->data);
		temp = temp->next;
	}
}

int	ft_check_pos(t_list **begin, int num)
{
	t_list	*tmp;
	int		pos;

	if (!begin || !(*begin))
		return (-1);
	pos = 0;
	tmp = (*begin);
	while (tmp)
	{
		if (*(int *)tmp->data > num)
		{
			pos++;
		}
		tmp = tmp->next;
	}
	return (pos);
}

/*THANKS FGRADIA FOR FT_CHECK_POS FUNCTION*/