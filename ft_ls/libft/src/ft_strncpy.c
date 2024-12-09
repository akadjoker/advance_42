

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*dst_cpy;
	size_t	i;

	i = 0;
	dst_cpy = dst;
	while (*src && i++ < len)
		*dst++ = *src++;
	while (i++ < len)
		*dst++ = 0;
	return (dst_cpy);
}
