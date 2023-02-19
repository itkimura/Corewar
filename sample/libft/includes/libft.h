/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 09:13:31 by leotran           #+#    #+#             */
/*   Updated: 2022/11/20 23:57:30 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 5
# define FD_SIZE 8192
# define MAX_LONG 
# define MIN_LONG 

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*previous;
	struct s_dlist	*next;
}					t_dlist;

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
int		ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

size_t	ft_strlcat(char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *str);

void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(const char *s, char (*f)(char));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strequ(const char *s1, const char *s2);
int		ft_strnequ(const char *s1, const char *s2, size_t n);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s);
char	**ft_strsplit(const char *s, char c, int *arrsize);
char	*ft_itoa(int n);
void	ft_putchar(int c);
void	ft_putstr(const char *s);
void	ft_putendl(const char *s);
void	ft_putnbr(long long n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));

void	ft_lstaddend(t_list **alst, t_list *new);
void	ft_lstdelend(t_list **alst, void (*del)(void *, size_t));
void	ft_lstswap(t_list **list);

int		ft_lstsize(t_list **lst);
t_dlist	*ft_dlstnew(void const *content, size_t content_size);
void	ft_dlstdelfront(t_dlist **alst, void (*del)(void *, size_t));
void	ft_dlstaddend(t_dlist **alst, t_dlist *new);
void	ft_dlstaddfront(t_dlist **alst, t_dlist *new);
int		ft_countstrings(const char *s, char c);
char	*ft_strccpy(char *src, int c);
int		ft_get_next_line(const int fd, char **line);
void	ft_foreach(int *tab, int length, void (*f)(int));
void	ft_putaddr(void *arr);
void	ft_put_u_nbr(unsigned long long n);
int		ft_uint_base_count(unsigned long long num, int base);
int		ft_int_base_count(long long num, int base);
size_t	ft_float_count(long double num, int precision, int precision_flag);
char	*ft_uitoa_base(unsigned long long num, int base, int flag);
char	*ft_itoa_base(long long num, int base, int flag);
char	*ft_ftoa(long double num, int precision_flag, int precision);
char	*ft_strjoin_update(char const *s1, char const *s2);
void	ft_swap(int *a, int *b);
int		ft_printf(const char *format, ...);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
long	ft_atol(const char *nptr);

#endif
