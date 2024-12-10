#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	char *s_iter;

	s_iter = (char *)s;
	while (*s_iter) {
		if (*s_iter == (char)c)
			return (s_iter);
		s_iter++;
	}
	return (*s_iter == (char)c ? s_iter : NULL);
}
