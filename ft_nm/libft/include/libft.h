#ifndef LIBFT_H
#define LIBFT_H

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strdup(const char *s1);
int ft_strcmp(const char *s1, const char *s2);
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(const char *s, int fd);
char *ft_strappend(char *dest, char const *src);
t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **lst, t_list *new);
void ft_lstiter(t_list *lst, void (*f)(void *));
void ft_putnbr_hex_fd(long long n, size_t width, int fd);
size_t ft_lstsize(t_list *lst);
void ft_strlower(char *str);
void ft_putchar_width_fd(char c, size_t width, int fd);
char *ft_strchr(const char *s, int c);
size_t ft_strlcpy_ex(char *dst, const char *src, size_t dstsize, char *ignore,
					 int lowercase);
char *ft_strdup_ex(const char *s1, char *ignore, int lowercase);

#endif // LIBFT_H
