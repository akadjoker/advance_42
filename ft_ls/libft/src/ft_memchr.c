
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cp;
	unsigned char	d;

	d = (unsigned char)c;
	s_cp = (unsigned char *)s;
	while (n--)
		if (d == *s_cp++)
			return (s_cp - 1);
	return (NULL);
}
