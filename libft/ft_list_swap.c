/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 18:02:17 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/03 02:36:46 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_pre_swap(t_list **begin, t_list **node1, t_list **node2)
{
	int		index1;
	int		index2;
	t_list	*temp3;

	if (!begin || (!(*begin)) || !*node1 || !*node2 || (*node1 == *node2))
		return (NULL);
	index1 = ft_list_index_node(begin, *node1);
	index2 = ft_list_index_node(begin, *node2);
	if (index1 > index2)
	{
		temp3 = *node1;
		*node1 = *node2;
		*node2 = temp3;
	}
	if (abs(index1 - index2) != 1)
		temp3 = (*node1)->next;
	else
		temp3 = *node1;
	return (temp3);
}

void	ft_list_swap(t_list **begin, t_list *node1, t_list *node2)
{	
	t_list		*temp;
	t_list		*temp2;
	t_list		*temp3;

	if (!begin || (!(*begin)) || !node1 || !node2 || (node1 == node2))
		return ;
	temp3 = ft_pre_swap(begin, &node1, &node2);
	temp = ft_list_find_prev_node_by_node(begin, node1);
	temp2 = ft_list_find_prev_node_by_node(begin, node2);
	if (!temp || !temp2 || !temp3)
		return ;
	if (temp == (t_list *)begin)
		 *begin = node2;
	else
		temp->next = node2;
	temp2->next = node1;
	node1->next = node2->next;
	node2->next = temp3;
	return ;
}

/*
SERVE IL PRE_SWAP PER 2 MOTIVI:
--->PER LO SWAP DEI NODI INDIFFERENTEMENTE DALLA LORO POSIZIONE, 
	CIOE' SE UNO STA AVANTI E L'ALTRO DIETRO O VICEVERSA
	NON FA DIFFERENZA POICHE' LI SCAMBIA PRIMA:
	if (index1 > index2)
	{
		temp3 = *node1;
		*node1 = *node2;
		*node2 = temp3;
	}
--->POI TRAMITE QUESTO PASSAGGIO:
	if (abs(index1 - index2) != 1)
		temp3 = (*node1)->next;
	else
		temp3 = *node1;
	VEDE SE UN NODO E' LONTANO DI PIU DI 1 POSIZIONE (PRIMA CONDIZIONE) 
	O SE E' PROSSIMO ALL'ALTRO(SECONDA CONDIZIONE) E SETTA DI 
	CONSEGUENZA TEMP3 AUSILIARIO DELLO SWAP
*/