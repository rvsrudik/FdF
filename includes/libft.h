/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:58:33 by vrudenko          #+#    #+#             */
/*   Updated: 2016/12/05 15:31:36 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lststrsplit(char const *s, char c);
void				ft_bzero(void *s, size_t n);
int					ft_countchars(char *str, char c);
int					ft_countsplit(char *str, char c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *tmp1, const void *tmp2, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
char				*ft_runspace_back(char *str);
char				*ft_runstr(char *str, char c);
char				*ft_strchr(const char *s, int c);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlen(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strnew(size_t size);
int					ft_isprint(int c);
char				**ft_strsplit(char const *s, char c);
void				ft_putendl_fd(char const *s, int fd);
void				ft_memdel(void **ap);
char				*ft_strncpy(char *dest, const char *src, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putstr(char const *str);
char				*ft_itoa(int nbr);
char				*ft_strncat(char *s1, const char *s2, size_t n);
void				ft_putnbr_fd(int n, int fd);
int					ft_isascii(int c);
char				*ft_strcat(char *s1, const char *s2);
int					ft_isdigit(int c);
char				*ft_runspace(char *str);
char				*ft_runchar(char *str, char c);
char				*ft_strcpy(char *dest, const char *src);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				ft_putchar(char c);
char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtoend(char *str);
char				*ft_strtrim(char const *s);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strnstr(const char *str, const char *to_f, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
void				ft_putnbr(int nb);
void				ft_strclr(char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_isdigid(char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_list_size(t_list *tmp);
void				ft_lstdelone(t_list **alst, void(*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstpushback(t_list *begin_list, void *data, size_t c_s);

#endif
