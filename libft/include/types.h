/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:05:43 by arrigo            #+#    #+#             */
/*   Updated: 2021/05/04 21:53:02 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
			/*TYPE CHAR__SIZE 1*/
# define T_C	0
			/*TYPE CHAR *_SIZE 8*/
# define T_S	1
			/*TYPE INT__SIZE 4*/
# define T_I	2
			/*TYPE UNS INT__SIZE 4*/
# define T_U	3
			/*TYPE LONG INT__SIZE 8*/
# define T_LI	4	
			/*TYPE LONG LONG INT__SIZE 8*/
# define T_LLI	5
			/*TYPE UNS LONG__SIZE 8*/
# define T_LU	6
			/*TYPE UNS LONG LONG__SIZE 8*/
# define T_LLU	7
			/*TYPE FLOAT__SIZE 4*/
# define T_F	8
			/*TYPE  DOUBLE__SIZE 8*/
# define T_LF	9

# define LIMIT_UP_INT 2147483647
# define LIMIT_DOWN_INT -2147483648

#endif