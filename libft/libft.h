/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:24:14 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/03 10:05:30 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//==== LIBFT ===//

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				ft_bzero(void *s, size_t n);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
void				*ft_calloc(size_t count, size_t size);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
//==== LIBFT BONUS ===//
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
//=== ADDED FUNCTIONS ===/
char				*ft_costume_strchr(const char *str, int c);
int					ft_abs(int n);
//==== FT_PRINTF ===//

int					ft_printf(const char *placeholder, ...);
int					ft_placeholder(char placeholder, va_list args);
int					ft_putnbr_base(long n, int base, char c);
int					ft_putptr(void *p, char c);
int					ft_putstr(char *str);
int					ft_putchar(int c);
int					ft_putptr_base(unsigned long n, int base, char c);

//==== GET_NEXT_LINE ===//
char	*get_next_line(int fd);


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif // BUFFER_SIZE

# ifndef INVALID_FD
#  define INVALID_FD -77
# endif // INVALID_FD

// unsigned int		ft_strlen_gnl(char *str);
// char				*ft_strdup_gnl(char *s1);
// char				*ft_strjoin_gnl(char *s1, char *s2);
// char				*ft_strchr_gnl(char *str, int c);
char				*get_next_line(int fd);

#endif