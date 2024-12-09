

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*cp_dst;
	const unsigned char	*cp_src;
	unsigned char		d;

	d = (unsigned char)c;
	cp_dst = (unsigned char *)dst;
	cp_src = (const unsigned char *)src;
	while (n--)
	{
		*cp_dst++ = *cp_src++;
		if (d == *(cp_dst - 1))
			return (cp_dst);
	}
	return (NULL);
}
