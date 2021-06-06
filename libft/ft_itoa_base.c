/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:05:07 by arrigo            #+#    #+#             */
/*   Updated: 2021/04/30 01:29:06 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_size_nbr_diffbase(size_t n, char *base)
{
	size_t	i;
	int		x;

	x = ft_strlen(base);
	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / x;
		i++;
	}
	return (i);
}

char	*ft_itoa_base_uns(size_t n, char *base)
{
	char	*str;
	int		x;
	int		size_base;
	int		len;

	len = ft_size_nbr_diffbase(n, base);
	size_base = ft_strlen(base);
	x = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len-- >= x)
	{
		str[len] = base[(n % size_base)];
		n = n / size_base;
	}
	return (str);
}
