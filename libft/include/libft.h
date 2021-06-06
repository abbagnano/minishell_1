/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arrigo <arrigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:30:53 by aviolini          #+#    #+#             */
/*   Updated: 2021/06/03 07:24:42 by arrigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
/* TO USE LIBRARY: make && gcc -Wall -Wextra -Werror main.c -L. -lft */
/* NON CI SONO PRINTF */
//# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include "get_next_line.h"
# include "list.h"
# include "struct.h"
# include "types.h"

# define BASE16 "0123456789abcdef"
# define BASE16X "0123456789ABCDEF"
# define BASE10 "0123456789"

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base_uns(size_t n, char *base);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
/*STR */
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(long long int n, int fd);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace_or_tab(int c);
int					ft_isprint(int c);

size_t				ft_strlen(const char *str);
int					ft_str_is_lowercase(char *str);
int					ft_str_is_uppercase(char *str);
char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *str);

char				*ft_strcpy(char *dest, char *src);
char				*ft_strncpy(char *dest, char *src, unsigned int n);
size_t				ft_strlcpy(char *dest, const char *src, size_t destsize);
int					ft_strchr(char *str, char c);
char				*ft_strrchr(const char *str, int c);

int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strcat(char *dest, char *src);
char				*ft_strncat(char *dest, char *src, unsigned int nb);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

char				*ft_strstr(char *str, char *to_find);
char				*ft_strnstr(const char *str, const char *needle, size_t l);

/*MATH*/
int					ft_recursive_factorial(int nb);
int					ft_recursive_power(int nb, int power);
int					ft_fibonacci(int index);
int					ft_sqrt(int nb);
int					ft_is_prime(int nb);

/*MEMORY*/
void				ft_bzero(void *str, size_t len);
void				*ft_memset(void *str, int c, size_t len);
void				*ft_memcpy(void *dest, const void *src, size_t num);
void				*ft_memccpy(void *dest, const void *src, int c, size_t l);

void				*ft_memchr(const void *str, int c, size_t len);
int					ft_memcmp(const void *str1, const void *str2, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t len);

/*MALLOC*/
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);

/*MATR_TOOLS*/
										//PRRINT A MATRIX, CONTENT TYPE STRING 
void				ft_matr_print_str(char *name, char **matrix);
										//DEL A MATRIX AND FREE CONTENT
int					ft_matr_del_and_free(char ***matrix);
										//RETURN THE NUMBER OF RAWS IN A MATRIX
										//RETURN -1 IF THE MATRIX NOT EXIST
int					ft_matr_size(char **matrix);
										//ADD A ROW AT THE END OF A MATRIX
										//CONTENT STR 
int					ft_matr_add_row_str(char ***matrix, char *s);

/*FT_READ_FD*/
										//READ A FILE DESCRIPTOR
										//RETURN THE FULL CONTENT OF FD IN A STRING
char				*ft_read_fd(int fd);

#endif
