/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeiflin <akeiflin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 23:02:11 by niguinti          #+#    #+#             */
/*   Updated: 2020/03/01 12:28:54 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 1024
# include <string.h>
# define NONE 0000
# define FIRST 0001
# define SECOND 0010
# define BOTH 0111
# undef tab

typedef struct	s_tab
{
	char			**tab;
	size_t			used;
	size_t			initial;
}				t_tab;

char			**ft_split_n_trim(char *s, char c);
void			ft_sort_tab(char **tab, int (*f)());
int				ft_atoi(const char *str);
char			*ft_ftoa(long double f, short prec);
char			*ft_strrev(char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalnum_str(char *str);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isdigits(char *c);
int				ft_isportable(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
char			*ft_itoa(long long int n);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
int				ft_putchar(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(const char *s);
void			ft_putstr_fd(const char *s, int fd);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, char c);
int				ft_strichr(const char *s, char c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
char			*ft_strcdup(const char *s1, char c);
int				ft_strequ(const char *s1, const char *s2);
void			ft_striter(char	*s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strjoinf(char *s1, char *s2, short type);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_strclen(const char *s, char c);
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
															size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(const char *s, char c);
char			*ft_strsub(char const *s, size_t start, size_t len);
char			*ft_strtrim(const char *s);
char			*ft_strtrimf(char *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_itoa_base(int value, int base, int caps);
int				ft_nbrlen_base(long long n, int base);
void			*ft_calloc(size_t size);
char			*ft_strljoin(char *s1, char *s2, char to_free);
char			*ft_strreplace(char *str, char *to_find, char *replace_str);
void			*ft_free(void *alloced);
char			*ft_vjoin(int n, ...);
void			ft_vprint(int n, ...);
void			ft_vprintfd(int fd, int n, ...);
int				ft_isalldigit(char *str);
size_t			ft_tablen(char **tab);
#endif
