/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:55:19 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/03 01:06:37 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_strutt
{
	char			c;
	char			*str;
	int				num;
	int				*ptr_num;
	void			*ptr_void;
}
					t_strutt;

void	ft_struct_print_struct(t_strutt *strutt);
void	ft_struct_zero_all_bytes(t_strutt *strutt);
int		ft_struct_copy_struct(t_strutt *dest, t_strutt *src);

#endif