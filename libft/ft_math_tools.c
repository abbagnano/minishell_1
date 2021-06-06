/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:27:13 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/30 01:53:38 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_recursive_factorial(int nb)
{
	if (nb < 0)
		return (0);
	if (nb == 0)
		return (1);
	else
		return (nb * ft_recursive_factorial(nb - 1));
}

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	else
		return (nb * ft_recursive_power(nb, power - 1));
}

int	ft_fibonacci(int index)
{
	if (index < 0)
		return (-1);
	if (index == 0)
		return (0);
	if (index == 1)
		return (1);
	else
		return (ft_fibonacci(index - 2) + ft_fibonacci(index - 1));
}

int	ft_sqrt(int nb)
{
	int	i;

	i = 1;
	while ((i * i) < nb)
		i++;
	if ((i * i) > nb)
		return (0);
	else
		return (i);
}

int	ft_is_prime(int nb)
{
	int	i;

	if (nb < 2)
		nb = nb * (-1);
	i = 2;
	while ((nb % i) != 0)
		i++;
	if (i == nb)
		return (1);
	else
		return (0);
}
