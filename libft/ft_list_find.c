/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:00:48 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/13 00:44:44 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_list_find_prev_node_by_node(t_list **begin, t_list *node)
{
	t_list	*temp;
	t_list	*temp2;

	if (!begin || !(*begin) || !node)
		return (NULL);
	temp = *begin;
	if (temp == node)
	{	
		temp2 = temp;
		temp = (t_list *)begin;
		temp->next = temp2;
		return (temp);
	}
	while (temp)
	{
		if ((temp)->next != node)
			temp = temp->next;
		else
			return (temp);
	}
	return (NULL);
}

t_list	*ft_list_find_prev_node_by_data(t_list **begin, void *data)
{
	t_list	*temp;
	t_list	*temp2;

	if (!begin || !(*begin))
		return (NULL);
	temp = *begin;
	if (*(int *)(temp->data) == *(int *)data)
	{	
		temp2 = temp;
		temp = (t_list *)begin;
		temp->next = temp2;
		return (temp);
	}
	while (temp && temp->next)
	{
		if (*(int *)(temp->next->data) != *(int *)data)
			temp = temp->next;
		else
			return (temp);
	}
	return (NULL);
}

t_list	*ft_list_find_node_by_data(t_list **begin, void *data)
{
	t_list	*temp;

	if (!begin || !(*begin))
		return (NULL);
	temp = *begin;
	while (temp)
	{
		if (*(int *)(temp->data) != *(int *)data)
			temp = temp->next;
		else
			return (temp);
	}
	return (NULL);
}

t_list	*ft_list_find_last_node(t_list **begin)
{
	t_list	*temp;

	if (!begin)
		return (NULL);
	if (!(*begin))
		return ((t_list *)begin);
	temp = *begin;
	if (!(temp->next))
		return (temp);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_list	*ft_list_find_next_node(t_list **begin, t_list *node)
{
	if (!begin || !(*begin) || !node)
		return (NULL);
	if ((t_list *)begin == node)
		return (*begin);
	if (!node->next)
		return (NULL);
	node = node->next;
	return (node);
}
