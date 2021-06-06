/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 11:29:39 by aviolini          #+#    #+#             */
/*   Updated: 2021/05/03 03:04:09 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h" 

void	ft_struct_print_struct(t_strutt *strutt)
{
	int				len;
	int				i;
	unsigned char	*one_byte;

	if (!strutt)
		return ;
	len = sizeof(*strutt);
	ft_putstr_fd("\n===>SIZE STRUCT: ", 1);
	ft_putnbr_fd(len, 1);
	ft_putstr_fd(" bytes\n", 1);
	ft_putstr_fd("===>STRUCT : ", 1);
	i = -1;
	one_byte = (unsigned char *)(strutt);
	while (++i < len)
	{	
		if (i % 8 == 0)
			ft_putstr_fd(" \n| ", 1);
		else
			ft_putchar_fd('-', 1);
		ft_putstr_fd(ft_itoa_base_uns(one_byte[i], BASE16), 1);
	}
	ft_putchar_fd('\n', 1);
}

void	ft_struct_zero_all_bytes(t_strutt *strutt)
{
	int				len;
	int				i;
	unsigned char	*one_byte;

	if (!strutt)
		return ;
	i = -1;
	len = sizeof(*strutt);
	one_byte = (unsigned char *)strutt;
	while (++i < len)
		one_byte[i] = 0x0;
}

int	ft_struct_copy_struct(t_strutt *dest, t_strutt *src)
{	
	int				len;
	int				i;
	unsigned char	*one_byte_dest;
	unsigned char	*one_byte_src;

	if (!dest || !src)
		return (0);
	one_byte_dest = (unsigned char *)dest;
	one_byte_src = (unsigned char *)src;
	i = -1;
	len = sizeof(*src);
	while (++i < len)
		one_byte_dest[i] = one_byte_src[i];
	return (1);
}
