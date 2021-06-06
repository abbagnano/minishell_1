/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:38:10 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/31 12:08:38 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_save_buf(char *buf, char *s)
{
	char	*save;

	if (!s)
		s = ft_strdup(buf);
	else
	{
		save = s;
		s = ft_strjoin(s, buf);
		free(save);
	}
	return (s);
}

char	*ft_read_fd(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*s;
	int		r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r = 1;
	s = NULL;
	while (r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free(s);
			return (NULL);
		}
		buf[r] = '\0';
		s = ft_save_buf(buf, s);
	}
	return (s);
}
