/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:32:33 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/30 01:55:35 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_memchr(const void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (*(unsigned const char *)(str + i) == (unsigned char)c)
			return ((unsigned char *)str + i);
		i++;
	}
	return (NULL);
}

int	ft_memcmp(const void *str1, const void *str2, size_t len)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (i < len)
	{
		if (*(s1 + i) != *(s2 + i))
			return (*(s1 + i) - *(s2 + i));
		i++;
	}
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (src < dest)
	{
		while (len)
		{
			len--;
			*(unsigned char *)(dest + len) = *(unsigned const char *)
				(src + len);
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
