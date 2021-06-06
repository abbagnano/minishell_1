/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matr_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 08:48:43 by arrigo            #+#    #+#             */
/*   Updated: 2021/06/03 07:25:27 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_matr_print_str(char *name, char **matrix)
{
	int	i;

	i = -1;
	if (!name)
		return (ft_putstr_fd("Empty name\n", 1));
	if (!matrix || !(*matrix))
		return (ft_putstr_fd("Empty Matrix\n", 1));
	ft_putstr_fd(name, 1);
	ft_putstr_fd(":\n", 1);
	while (matrix[++i])
	{
		ft_putnbr_fd((int)i, 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd(matrix[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

int	ft_matr_del_and_free(char ***matrix)
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

int	ft_matr_size(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (-1);
	while (matrix[i])
		i++;
	return (i);
}

int	ft_matr_add_row_str(char ***matrix, char *s)
{
	int		i;
	int		len;
	char	**new;

	if (!(*matrix) || !s)
		return (0);
	len = ft_matr_size(*matrix);
	i = -1;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (0);
	while ((*matrix)[++i])
	{
		new[i] = ft_strdup((*matrix)[i]);
		if (!new)
			return (ft_matr_del_and_free(&new));
	}
	new[i] = ft_strdup(s);
	if (!new)
		return (ft_matr_del_and_free(&new));
	new[++i] = NULL;
	ft_matr_del_and_free(&(*matrix));
	*matrix = new;
	return (1);
}
