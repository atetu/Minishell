/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:28:33 by thgermai          #+#    #+#             */
/*   Updated: 2020/08/30 12:48:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <strings.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# define BUFFER_SIZE 512
# define HEXADECIMAL "0123456789abcdef"
# define VALID_VALUE "cspdiuxX%"
# define VALID_FLAGS "-.0*"
# define LEFT 1
# define RIGHT 0

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_param
{
	int				specifier;
	int				width;
	int				precision;
	int				justify;
	char			fill;
}					t_param;

typedef struct		s_ptrlst
{
	void			*ptr;
	void			(*fptr)(void *);
}					t_ptrlst;

int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_find_in(char *str, char c);
int					ft_exit(int ret, int n, ...);
int					ft_lstsize(t_list	*lst);
int					ft_atoi(const char *str);
unsigned long long	ft_atoll(const char *str);
int					get_next_line(int fd, char **line, int *go_on);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_printf(const char *str, ...);
char				*ft_str_toupper(char *str);
char				*ft_str_tolower(char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_f12(char const *s1, char const *s2);
char				*ft_strjoin_f1(char const *s1, char const *s2);
char				*ft_strjoin_f2(char const *s1, char const *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_itoa(int n);
char				*ft_itoa_unsigned(unsigned int n);
char				*ft_itoa_base(unsigned int n, char *base);
char				*ft_itoa_address(unsigned long long int n);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(const char *s, char c);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				ft_memdel(void **ap);
void				*ft_exit_ptr(void *ret, int n, ...);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putnbr_base(int nbr, char *base);
void				*ft_calloc(size_t count, size_t size);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/*
** ft_printf
*/
int					ft_printf(const char *str, ...);
int					next_arg_index(const char *str);
const char			*ft_refresh_str(const char *str);
int					define_type(char c);
t_param				*parsing_param(const char *str, va_list args);
int					pf_fill_char(va_list args, t_param *param);
int					pf_fill_str(va_list args, t_param *param);
int					pf_fill_add(va_list args, t_param *param);
int					pf_fill_deci(va_list args, t_param *param);
int					pf_fill_int(va_list args, t_param *param);
int					pf_fill_unsi(va_list args, t_param *param);
int					pf_fill_hexa(va_list args, t_param *param);
int					pf_fill_hexa_caps(va_list args, t_param *param);
int					pf_fill_modulo(va_list args, t_param *param);
char				*fill_width_left(char *str, t_param *param);
char				*fill_width_right(char *str, t_param *param);
char				*check_width_num(char *str, t_param *param);
char				*check_precision_num(char *str, t_param *param);
char				*fill_precision(char *str, t_param *param);
int					ft_printf_e(const char *str, ...);
int					pf_fill_char_e(va_list args, t_param *param);
int					pf_fill_str_e(va_list args, t_param *param);
int					pf_fill_add_e(va_list args, t_param *param);
int					pf_fill_deci_e(va_list args, t_param *param);
int					pf_fill_int_e(va_list args, t_param *param);
int					pf_fill_unsi_e(va_list args, t_param *param);
int					pf_fill_hexa_e(va_list args, t_param *param);
int					pf_fill_hexa_caps_e(va_list args, t_param *param);
int					pf_fill_modulo_e(va_list args, t_param *param);
/*
**	garbage collector ptr
*/
void				ft_free_ptrlst(t_list **lst);
void				ft_del_ptr(t_list **lst, void *to_del);
void				*ft_add_ptr(void *ptr, t_list **lst, void (*fptr)(void *));
void				ft_print_add_lst(t_list **lst);

#endif
