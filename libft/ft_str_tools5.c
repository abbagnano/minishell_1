/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tools5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:16:29 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/03 02:59:23 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	x;
	int				res;

	x = 0;
	while (s1[x] || s2[x])
	{
		if (s1[x] != s2[x])
		{
			res = (s1[x] - s2[x]);
			return (res);
		}
		else
			x++;
	}
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)

{
	size_t	i;

	if (!str1 || !str2)
		return (-1);
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
			return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
		i++;
	}
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	x;
	unsigned int	y;

	if (!dest || !src)
		return (NULL);
	x = 0;
	y = 0;
	while (dest[x])
		x++;
	while (src[y])
	{
		dest[x] = src[y];
		y++;
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	x;
	unsigned int	y;

	if (!dest || !src)
		return (NULL);
	x = 0;
	y = 0;
	while (dest[x])
		x++;
	while (y < nb && src[y])
	{
		dest[x] = src[y];
		y++;
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	while (dst[i] && i < size)
		i++;
	while (src[x] && (i + x + 1) < size)
	{
		dst[i + x] = src[x];
		x++;
	}
	if (i < size)
		dst[i + x] = '\0';
	return (i + ft_strlen(src));
}
