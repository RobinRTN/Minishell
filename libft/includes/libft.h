/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrettien <rrettien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:18:21 by rrettien          #+#    #+#             */
/*   Updated: 2024/02/21 14:40:34 by rrettien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (42)
# endif

int					ft_atoi(const char *str);
void				ft_bzero(void *str, size_t len);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
// void				ft_lstadd_back(t_list **lst, t_list *new);
// void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
int					ft_memcmp(const void *s1, const void *s2, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memset(void *str, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *str, int c);
char				*ft_strdup(const char *str);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strnjoin(int nbr, char *format, ...);

// get next line
char				*get_next_line(int fd);
char				*fill_line(int fd, char *leftover, char *buffer);
char				*set_leftover(char *result);

// HELPERS
int					ft_compute_size(unsigned int num, int base);
int					ft_compute_size_long(unsigned long long num, int base);
int					is_command(char c);
char				*ft_unsigned_itoa(unsigned int num);

// PRINTERS FIRST
int					ft_printchar(int c);
int					ft_printstr(char *str);
int					ft_printptr(unsigned long long num);
int					ft_printnbr(int i);

// PRINTERS SECOND
int					ft_print_unsigned(unsigned int num);
int					ft_printhexa(unsigned int num, char x);
int					ft_printpercent(void);

// PRINTF
int					ft_print_tree(char c, va_list args);
int					ft_parser(char *str, va_list args);
int					ft_printf(const char *format, ...);

#endif
