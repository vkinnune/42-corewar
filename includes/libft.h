/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:47:36 by qnguyen           #+#    #+#             */
/*   Updated: 2021/11/07 01:47:36 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* # define ABS(Value) ((Value < 0) ? (-Value):(Value))
# define SMOL_NUM(value1, value2) (value1 < value2 ? value1 : value2)
# define BIG_NUM(value1, value2) (value1 > value2 ? value1 : value2) */

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct s_index
{
	int	str_idx;
	int	buf_idx;
	int	arr_idx;
}				t_index;

int			ft_abs(int n);

void		ft_arrdel(char ***arr);

int			ft_atoi(const char *str);

void		ft_bzero(void *b, size_t n);

void		*ft_calloc(size_t count, size_t size);

int			ft_countwords(const char *s, char c);

void		ft_d2base(unsigned long long n, int base, char x);

void		ft_d2base_fd(unsigned long long n, int base, char x, int fd);

int			ft_diglen(long long n);

int			ft_greaternum(int a, int b);

int			ft_isalnum(int c);

int			ft_isalpha(int c);

int			ft_isascii(int c);

int			ft_isdigit(int c);

int			ft_isprint(int c);

int			ft_isspace(int c);

char		*ft_itoa(long long n);

void		ft_linkdel(void *content, size_t content_size);

void		ft_lstadd_back(t_list **alst, t_list *new);

void		ft_lstadd(t_list **alst, t_list *new);

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list		*ft_lstlast(t_list *lst);

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_list		*ft_lstnew(void const *content, size_t content_size);

t_list		*ft_lststrsplit(const char *s, char c);

void		*ft_memalloc(size_t size);

void		*ft_memccpy(void *dst, const void *src, int c, size_t n);

void		*ft_memchr(const void *s, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_memcpy(void *dst, const void *src, size_t n);

void		ft_memdel(void **ap);

void		*ft_memmove(void *dst, const void *src, size_t len);

void		*ft_memset(void *b, int c, size_t len);

void		ft_putchar_fd(char c, int fd);

long int	ft_pow(int num, int power);

int			ft_putchar(char c);

void		ft_putendl_fd(char const *s, int fd);

void		ft_putendl(char const *s);

int			ft_putfloat(long double lift, int prec);

int			ft_putfloat_fd(long double lift, int prec, int fd);

void		ft_putnbr_fd(long long n, int fd);

void		ft_putnbr(long long n);

void		ft_putstr_fd(char *s, int fd);

int			ft_putstr(char *s);

int			ft_smallernum(int a, int b);

int			ft_sqrt(int num);

char		*ft_strcat(char *dest, const char *src);

char		*ft_strchr(const char *s, int c);

void		ft_strclr(char *s);

int			ft_strcmp(const char *str1, const char *str2);

char		*ft_strcpy(char *dest, const char *src);

void		ft_strdel(char **as);

char		*ft_strdup(const char *src);

int			ft_strequ(char const *s1, char const *s2);

void		ft_striter(char *s, void (*f)(char *));

void		ft_striteri(char *s, void (*f)(unsigned int, char *));

char		*ft_strjoin(char const *s1, char const *s2);

size_t		ft_strlcat(char *dest, const char *src, size_t size);

size_t		ft_strlen(const char *str);

char		*ft_strmap(char const *s, char (*f)(char));

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char		*ft_strncat(char *dest, const char *src, size_t n);

int			ft_strncmp(const char *str1, const char *str2, size_t n);

char		*ft_strncpy(char *dest, const char *src, size_t n);

int			ft_strnequ(char const *s1, char const *s2, size_t n);

char		*ft_strnew(size_t size);

char		*ft_strnstr(const char *str, const char *to_find, size_t len);

char		*ft_strrchr(const char *s, int c);

char		**ft_strsplit(char const *s, char c);

char		*ft_strstr(const char *str, const char *to_find);

char		*ft_strsub(char const *s, unsigned int start, size_t len);

char		*ft_strtrim(char const *s);

void		ft_swap(int *a, int *b);

int			ft_toupper(int c);

int			ft_tolower(int c);

int			ft_udiglen(unsigned long long n, int base);

#endif
