/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 02:08:20 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/04 19:13:23 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_list_print_address(void *element)
{
	char	*address;

	if (!element)
	{
		ft_putstr_fd("NULL", 1);
		return ;
	}
	address = ft_itoa_base_uns((unsigned long long)element, BASE16);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(address, 1);
	free(address);
	return ;
}

int	ft_list_print_head(t_list **begin)
{
	int	size_list;

	if (!begin || !(*begin))
	{	
		ft_putstr_fd("\nLIST EMPTY\n", 1);
		return (0);
	}
	size_list = ft_list_size_list(begin);
	ft_putstr_fd("\n===>SIZE LIST: ", 1);
	ft_putnbr_fd(size_list, 1);
	if (size_list == 1)
		ft_putstr_fd(" node", 1);
	else
		ft_putstr_fd(" nodes", 1);
	ft_putstr_fd("\n==>START LIST:\n", 1);
	ft_putstr_fd("\n______address_list: ", 1);
	ft_list_print_address((t_list *)begin);
	ft_putstr_fd("\n|\n", 1);
	return (1);
}

int	ft_list_print_tail(t_list *temp)
{
	if (temp != NULL)
	{
		ft_putstr_fd("____addr_next_node = ", 1);
		ft_list_print_address((t_list *)temp);
		ft_putstr_fd("\n|", 1);
	}
	else
	{
		ft_putstr_fd("    addr_next_node = ", 1);
		ft_list_print_address((t_list *)temp);
	}	
	return (0);
}

void	ft_list_print_num(t_list **begin)
{
	int		c;
	t_list	*temp;

	if (!ft_list_print_head(begin))
		return ;
	temp = *begin;
	c = 0;
	while (temp)
	{
		c++;
		ft_putstr_fd("|-->address_this_node: ", 1);
		ft_list_print_address((t_list *)temp);
		ft_putstr_fd("\n    address.data = ", 1);
		ft_list_print_address((int *)temp->data);
		ft_putstr_fd("\n    content.data = ", 1);
		if (!((int *)temp->data))
			ft_putstr_fd("NULL", 1);
		else
			ft_putnbr_fd(*(int *)temp->data, 1);
		ft_putchar_fd('\n', 1);
		ft_list_print_tail(temp->next);
		ft_putchar_fd('\n', 1);
		temp = (temp)->next;
	}
	ft_putstr_fd("\n==>END LIST<==\n\n", 1);
}

void	ft_list_print_str(t_list **begin)
{
	int		c;
	t_list	*temp;

	if (!ft_list_print_head(begin))
		return ;
	temp = *begin;
	c = 0;
	while (temp)
	{
		c++;
		ft_putstr_fd("|-->address_this_node: ", 1);
		ft_list_print_address((t_list *)temp);
		ft_putstr_fd("\n    address.data = ", 1);
		ft_list_print_address((char *)temp->data);
		ft_putstr_fd("\n    content.data = ", 1);
		ft_putstr_fd(temp->data, 1);
		ft_putchar_fd('\n', 1);
		ft_list_print_tail(temp->next);
		ft_putchar_fd('\n', 1);
		temp = (temp)->next;
	}
	ft_putstr_fd("\n==>END LIST<==\n\n", 1);
}
