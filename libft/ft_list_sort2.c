/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 00:35:15 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/27 07:10:44 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_list_sort_is_sort_incr_num(t_list **begin)
{
	t_list	*temp;

	if (!begin || !(*begin))
		return (0);
	if (!(*begin)->next)
		return (1);
	temp = *begin;
	while (temp->next)
	{
		if (*(int *)temp->data > *(int *)temp->next->data)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	ft_list_sort_is_sort_decr_num(t_list **begin)
{
	t_list	*temp;

	if (!begin || !(*begin))
		return (0);
	if (!(*begin)->next)
		return (1);
	temp = *begin;
	while (temp->next)
	{
		if (*(int *)temp->data < *(int *)temp->next->data)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	ft_list_sort_is_sort_incr_num_interval(t_list *start, t_list *end)
{
	if (!(start))
		return (0);
	if (!(start)->next)
		return (1);
	if (end)
		end = end->next;
	while (start->next != end)
	{
		if (*(int *)start->data > *(int *)start->next->data)
			return (0);
		start = start->next;
	}
	return (1);
}

int	ft_list_sort_is_sort_decr_num_interval(t_list *start, t_list *end)
{
	if (!(start))
		return (0);
	if (!(start)->next)
		return (1);
	if (end)
		end = end->next;
	while (start->next != end)
	{
		if (*(int *)start->data < *(int *)start->next->data)
			return (0);
		start = start->next;
	}
	return (1);
}
