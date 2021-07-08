/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aviol2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviolini <aviolini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 16:44:47 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/21 11:57:16 by aviolini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!(s))
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (((int)start < ft_strlen((char *)s)))
	{
		while (i < len)
		{
			*(ptr + i) = *(s + start + i);
			i++;
		}
		*(ptr + i) = '\0';
	}
	return (ptr);
}

int	ft_strjoin_over(char **s1, char const *s2)
{
	char		*ptr;
	size_t		i;
	size_t		lens1;
	size_t		lens2;

	i = -1;
	if (!(*s1) || !(s2))
		return (0);
	lens1 = ft_strlen((char *)(*s1));
	lens2 = ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!ptr)
		return (0);
	while (++i < lens1)
		ptr[i] = (*s1)[i];
	i = -1;
	while (++i < lens2)
		ptr[lens1 + i] = s2[i];
	ptr[lens1 + i] = '\0';
	free(*s1);
	*s1 = ptr;
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ptr;
	size_t		i;
	size_t		lens1;
	size_t		lens2;

	i = -1;
	if (!(s1) || !(s2))
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	lens2 = ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!ptr)
		return (NULL);
	while (++i < lens1)
		ptr[i] = s1[i];
	i = -1;
	while (++i < lens2)
		ptr[lens1 + i] = s2[i];
	ptr[lens1 + i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)str);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_free_matrix(char ***matrix)
{
	int	i;

	i = -1;
	if (!(*matrix))
		return (0);
	while ((*matrix)[++i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
	}
	free(*matrix);
	*matrix = NULL;
	return (0);
}
