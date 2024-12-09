

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_cp;
	const char	*src_cp;

	if (!dst && !src)
		return (NULL);
	dst_cp = (char *)dst;
	src_cp = (const char *)src;
	while (n--)
		*dst_cp++ = *src_cp++;
	return (dst);
}
