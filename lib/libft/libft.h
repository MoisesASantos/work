/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosantos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:54:00 by mosantos          #+#    #+#             */
/*   Updated: 2026/01/21 12:57:49 by sgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

//string functions
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_line(char *rest);
char	*get_update(char *rest);
char	*get_next_line(int fd);
char	*ft_sttrjoin(char *rest, const char *line);
char	*ft_engine(char **rest, int fd);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_puttchar_fd(char c, int fd);
int		ft_puttstr_fd(const char *str, int fd);
int		ft_putnbr_base_fd(unsigned long ptr, const char *base,
			int base_len, int fd);
int		ft_puttnbr_fd(int n, int fd);
int		ft_putnbr_unsigned_fd(unsigned int n, int fd);
int		ft_handle_pointer(void *ptr, int fd);
int		check_args(const char *str, va_list arg);
int		ft_printf(const char *str, ...);
int		is_valid_specifier(char c);
int		ft_sttrchr_nl(const char *str);
int		ft_quant_matrix(char **matrix);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *destination, const char *source, size_t size);
long	ft_atoll(const char *nptr, int *error_flag);
long	ft_atoll_base(const char *str, int base, int *error_flag);
//memory functions
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
//file functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
//alocation memory functions
void	*ft_calloc(size_t nmemb, size_t size);
//bonus
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *novo);
void	ft_lstadd_back(t_list **lst, t_list *novo);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);
#endif
