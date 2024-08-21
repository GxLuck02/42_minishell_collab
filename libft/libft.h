/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttreichl <ttreichl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:03:40 by ttreichl          #+#    #+#             */
/*   Updated: 2024/06/10 15:45:22 by ttreichl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define BUFFER_SIZE 100

int			ft_atoi(const char	*string);
void		ft_bzero(void *ptr, size_t nbroct);
void		*ft_calloc(size_t nbrelement, size_t elementsize);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);
int			ft_memcmp(const void *str1, const void *str2, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t nbroct);
void		*ft_memmove(void *dest, const void *src, size_t nbroct);
void		*ft_memset(void *ptr, int value, size_t len);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const	*s, char c);
char		*ft_strchr(const char	*string, int searchChar);
char		*ft_strdup(const char *src);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char	*dest, const char	*src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t lenght);
size_t		ft_strlen(const char *word);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *first, const char *second, size_t len);
char		*ft_strnstr(const char *string, const char *needle, size_t len);
char		*ft_strrchr(const char	*string, int searchChar);
char		*ft_strtrim(char const	*s1, char const	*set);
char		*ft_substr(char const	*s, unsigned int start, size_t len);
int			ft_tolower(int character);
int			ft_toupper(int character);
char		*get_next_line(int fd);
char		*gnl_strjoinfree(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isspace(char c);
const char	*ft_strstr(const char *x, const char *y);

typedef struct s_liste
{
	void			*content;
	struct s_list	*next;
}					t_liste;

t_liste		*ft_lstnew(void *content);
void		ft_lstadd_front(t_liste **lst, t_liste *new);
int			ft_lstsize(t_liste *lst);
t_liste		*ft_lstlast(t_liste *lst);
void		ft_lstadd_back(t_liste **lst, t_liste *new);
void		ft_lstdelone(t_liste *lst, void (*del)(void*));
void		ft_lstclear(t_liste **lst, void (*del)(void*));
void		ft_lstiter(t_liste *lst, void (*f)(void *));
t_liste		*ft_lstmap(t_liste *lst, void *(*f)(void *), void (*del)(void *));

int			ft_printchar(int c);
int			ft_printf(const char *start, ...);
int			ft_printhex(unsigned int c, const char format);
int			ft_printnbr(int num);
int			ft_printpercent(void);
int			ft_printptr(unsigned long long ptr);
int			ft_printstring(const char *string);
int			ft_printunsnbr(unsigned int c);

#endif
