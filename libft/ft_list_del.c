/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:02:53 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/05 10:36:31 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_list_del_list(t_list ***begin)
{
	t_list	*temp;
	t_list	*temp2;

	if (!*begin)
		return ;
	temp = **begin;
	temp2 = **begin;
	while (temp2)
	{
		temp2 = temp2->next;
		free(temp->data);
		free (temp);
		temp = temp2;
	}
	**begin = NULL;
	free(*begin);
	*begin = NULL;
}

void	ft_list_zero_node(t_list *node)
{
	int				len;
	int				i;
	unsigned char	*one_byte;

	i = -1;
	len = sizeof(*node);
	one_byte = (unsigned char *)node;
	free(node->data);
	node->data = NULL;
	while (++i < len - 8)
		one_byte[i] = 0;
}

void 	ft_list_zero_list(t_list **begin)
{
	t_list	*temp;

	temp = *begin;
	while (temp)
	{
		ft_list_zero_node(temp);
		temp = temp->next;
	}
}

void	ft_list_del_node_by_data(t_list **begin, void *data)
{
	t_list	*temp;
	t_list	*temp2;

	if (!begin || !(*begin))
		return ;
	temp = *begin;
	if (*(int *)temp->data == *(int *)data)
	{
		temp2 = temp->next;
		free(temp->data);
		free(temp);
		*begin = temp2;
		return ;
	}
	temp = ft_list_find_prev_node_by_data(begin, data);
	if (!temp)
		return ;
	temp2 = temp->next->next;
	free(temp->next);
	temp->next = temp2;
}

void	ft_list_del_node_by_node(t_list **begin, t_list *node)
{
	t_list	*temp;
	t_list	*temp2;

	if (!begin || !(*begin) || !node)
		return ;
	temp = *begin;
	if (temp == node)
	{
		temp2 = temp->next;
		free(temp->data);
		free(temp);
		*begin = temp2;
		return ;
	}
	temp = ft_list_find_prev_node_by_node(begin, node);
	if (!temp)
		return ;
	temp2 = temp->next->next;
	free(temp->next);
	temp->next = temp2;
}
