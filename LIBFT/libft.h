/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:35:55 by aelsayed          #+#    #+#             */
/*   Updated: 2025/01/29 11:22:27 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	char			*s;
	char			**arr;
}					t_alloc;

// memory functions
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_free(char *format, ...);
void				*int_free(char *format, ...);
t_alloc				*ft_malloc(char *format, int len, int wd, int slen);

// string fnctions
size_t				ft_strlen(const char *s);
size_t				ft_arrlen(char **arr);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t destsize);
char				*ft_strchr(const char *s, int c);
int					ft_strchr_index(const char *s, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s, char const *set);
char				**ft_split(char const *s, char b);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

// integer functions
void				ft_swap(int *a, int *b);
void				ft_putnbr(int n);
int					ft_atoi(const char *str);
char				*ft_itoa(int nb);

// ft_is fuctions
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

// file descriptor
void				ft_putchar_fd(char c, int ft);
void				ft_putnbr_fd(int c, int fd);
void				ft_putstr_fd(char const *c, int fd);
void				ft_putendl_fd(char const *s, int fd);
char				*get_next_line(int fd);
char				**ft_read(int fd, char *filename);

// linked lists
t_list				*ft_lstnew_bonus(void *content);
void				ft_lstadd_front_bonus(t_list **lst, t_list *new);
int					ft_lstsize_bonus(t_list *lst);
t_list				*ft_lstlast_bonus(t_list *lst);
void				ft_lstadd_back_bonus(t_list **lst, t_list *new);
void				ft_lstdelone_bonus(t_list *lst, void (*del)(void *));
void				ft_lstclear_bonus(t_list **lst, void (*del)(void *));
void				ft_lstiter_bonus(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap_bonus(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// printfd unctions
int					fd_putnbr(int fd, int n);
int					fd_putnbr_u(int fd, unsigned int n);
int					fd_putnbr_x(int fd, int n);
int					fd_putnbr_xx(int fd, int n);
int					fd_putchar(int fd, char c);
int					fd_putstr(int fd, char const *s);
int					fd_putptr(int fd, void *s);
int					fd_checker(int fd, int c, ...);
int					printfd(int fd, char const *s, ...);

#endif
