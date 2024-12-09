

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_cpy;
	unsigned char	d;

	d = (unsigned char)c;
	b_cpy = (unsigned char *)b;
	while (len--)
		*b_cpy++ = d;
	return (b);
}
