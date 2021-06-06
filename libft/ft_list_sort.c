/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:23:29 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/13 00:35:35 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_list_sort_incr_num(t_list **begin)
{
	t_list	*temp;
	t_list	*temp2;
	int		i;
	int		size;

	if (!begin || !(*begin) || !(*begin)->next)
		return ;
	temp = *begin;
	size = ft_list_size_list(begin);
	i = -1;
	while (++i < size - 1)
	{
		temp2 = temp->next;
		if (!temp2)
			return ;
		if (*(int *)temp->data > *(int *)temp2->data)
		{
			ft_list_swap(begin, temp, temp2);
			temp = *begin;
			i = -1;
		}
		else
			temp = temp->next;
	}
}

void	ft_list_sort_decr_num(t_list **begin)
{
	t_list	*temp;
	t_list	*temp2;
	int		i;
	int		size;

	if (!begin || !(*begin) || !(*begin)->next)
		return ;
	temp = *begin;
	size = ft_list_size_list(begin);
	i = -1;
	while (++i < size - 1)
	{
		temp2 = temp->next;
		if (!temp2)
			return ;
		if (*(int *)temp->data < *(int *)temp2->data)
		{
			ft_list_swap(begin, temp, temp2);
			temp = *begin;
			i = -1;
		}
		else
			temp = temp->next;
	}
}

void	ft_list_sort_incr_str(t_list **begin)
{
	t_list	*temp;
	t_list	*temp2;
	int		i;
	int		size;

	if (!begin || !(*begin) || !(*begin)->next)
		return ;
	temp = *begin;
	size = ft_list_size_list(begin);
	i = -1;
	while (++i < size - 1)
	{
		temp2 = temp->next;
		if (!temp2)
			return ;
		if (ft_strcmp((char *)temp->data, (char *)temp2->data) > 0)
		{
			ft_list_swap(begin, temp, temp2);
			temp = *begin;
			i = -1;
		}
		else
			temp = temp->next;
	}
}

void	ft_list_sort_decr_str(t_list **begin)
{
	t_list	*temp;
	t_list	*temp2;
	int		i;
	int		size;

	if (!begin || !(*begin) || !(*begin)->next)
		return ;
	temp = *begin;
	size = ft_list_size_list(begin);
	i = -1;
	while (++i < size - 1)
	{
		temp2 = temp->next;
		if (!temp2)
			return ;
		if (ft_strcmp((char *)temp->data, (char *)temp2->data) < 0)
		{
			ft_list_swap(begin, temp, temp2);
			temp = *begin;
			i = -1;
		}
		else
			temp = temp->next;
	}
}
