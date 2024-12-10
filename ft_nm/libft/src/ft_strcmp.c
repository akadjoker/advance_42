#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *s1_iter;
	unsigned char *s2_iter;

	s1_iter = (unsigned char *)s1;
	s2_iter = (unsigned char *)s2;
	while (*s1_iter && (*s1_iter == *s2_iter)) {
		s1_iter++;
		s2_iter++;
	}
	return (*s1_iter - *s2_iter);
}
