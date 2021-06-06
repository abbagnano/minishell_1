/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:57:08 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/05 11:30:02 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	**ft_list_init(void)
{	
	t_list	**new;

	new = (t_list **)malloc(sizeof(t_list *));
	if (!new)
		return (NULL);
	*new = NULL;
	return (new);
}

void	ft_list_add_node_back_list(t_list **begin, void *data, int type)
{
	t_list	*new;

	new = ft_list_find_last_node(begin);
	if (new == (t_list *)begin)
	{
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
			return ;
		*begin = new;
		new->next = NULL;
		new->data = ft_list_malloc_data_element(data, type);
		return ;
	}
	ft_list_add_node_after_node(new, data, type);
}

void	ft_list_add_node_front_list(t_list **begin, void *data, int type)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	new->next = *begin;
	new->data = ft_list_malloc_data_element(data, type);
	*begin = new;
}

t_list	*ft_list_add_node_after_node(t_list *node, void *data, int type)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = node->next;
	node->next = new;
	new->data = ft_list_malloc_data_element(data, type);
	return (new);
}

void	*ft_list_malloc_data_element(void *data, int type)
{
	void	*new;

	new = NULL;
	if (type == T_C)
	{
		new = (char *)malloc(sizeof(char));
		*(char *)new = *(char *)data;
	}
	else if (type == T_S)
	{
		new = ft_strdup((const char *)data);
	}
	else if (type == T_I)
	{
		new = (int *)malloc(sizeof(int));
		*(int *)new = *(int *)data;
	}
	else if (type == T_LI)
	{
		new = (long int *)malloc(sizeof(long int));
		*(long int *)new = *(long int *)data;
	}
	return (new);
}

/* DEPRECATED
t_list	*ft_list_new_node(void *data)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

t_list	**ft_list_add_new_list(void *data)
{
	t_list	**begin;
	t_list	*new_node;

	begin = (t_list **)malloc(sizeof(t_list *));
	new_node = (t_list *)malloc(sizeof(t_list));
	*begin = new_node;
	new_node->data = data;
	new_node->next = NULL;
	return (begin);
}
*/

/* FUNZIONA ANCHE COSI
void	ft_list_fill_data_element(void **new, void *data, int type)
{
	if (type == T_C)
	{
		*new = (char *)malloc(sizeof(char));
		*(char *)*new = *(char *)data;
	}
	else if (type == T_S)
	{
		*new = ft_strdup((const char *)data);
	}
	else if (type == T_I)
	{
		*new = (int *)malloc(sizeof(int));
		*(int *)*new = *(int *)data;
	}
	else if (type == T_LI)
	{
		*new = (long int *)malloc(sizeof(long int));
		*(long int *)*new = *(long int *)data;
	}
}
*/