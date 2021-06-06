/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:48:01 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/16 15:35:22 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_list_size_list(t_list **begin)
{
	int		i;
	t_list	*temp;

	if (!begin || !(*begin))
		return (0);
	temp = *begin;
	i = 0;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	ft_list_size_list_interval(t_list *start, t_list *end)
{
	int		i;

	if (!start)
		return (0);
	i = 0;
	while (start != end)
	{
		i++;
		start = start->next;
	}
	return (++i);
}

int	ft_list_index_node(t_list **begin, t_list *node)
{
	t_list	*temp;
	int		i;

	if (!begin || !(*begin))
		return (-1);
	i = 0;
	temp = *begin;
	while (temp != node)
	{	
		temp = temp->next;
		if (!temp)
			return (-1);
		i++;
	}
	return (i);
}
