/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:52:31 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/12 21:35:13 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_list_move_node_after_node(t_list **begin, t_list *src, t_list *dest)
{
	t_list	*temp;

	if (!begin || (!(*begin)) || !src || !dest || (src == dest))
		return ;
	temp = ft_list_find_prev_node_by_node(begin, src);
	if (temp == (t_list *)begin)
		*begin = src->next;
	else
		temp->next = src->next;
	if (dest == (t_list *)begin)
	{
		temp = *begin;
		*begin = src;
	}
	else
	{
		temp = dest->next;
		dest->next = src;
	}
	src->next = temp;
	return ;
}
