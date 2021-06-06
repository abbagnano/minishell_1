/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tools6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:25:36 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/03 03:03:54 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (!str || !to_find)
		return (NULL);
	i = 0;
	while (to_find[i])
		i++;
	if (i == 0)
		return (str);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *str, const char *needle, size_t l)
{
	size_t	i;
	size_t	y;

	if (!str || !needle)
		return (NULL);
	i = 0;
	y = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)str);
	while (str[i] && i < l)
	{
		while (needle[y] == str[i + y])
		{
			if (needle[y + 1] == '\0' && l > (y + i))
				return ((char *)str + i);
			y++;
		}
		y = 0;
		i++;
	}
	return (NULL);
}
