/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 12:20:25 by aviolini          #+#    #+#             */
/*   Updated: 2021/04/30 01:57:20 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_cntwrds(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

size_t	ft_idxwrd(char const *s, char c, size_t i)
{
	while (s[i] != c && s[i])
		i++;
	return (i - 1);
}

char	**ft_fill(char **ptr, char const *s, char c)
{
	size_t	y;
	size_t	size;
	size_t	z;
	size_t	start;
	size_t	end;

	start = 0;
	z = 0;
	while (s[start])
	{
		if (s[start] != c)
		{
			end = (ft_idxwrd(s, c, start));
			size = end - start + 1;
			ptr[z] = ft_substr(s, start, size);
			y = 0;
			while (y < size)
				ptr[z][y++] = s[start++];
			ptr[z++][y] = '\0';
			start = end;
		}
		start++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	count;

	if (!(s))
		return (NULL);
	count = ft_cntwrds(s, c);
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	ft_fill(ptr, s, c);
	ptr[count] = NULL;
	return (ptr);
}
