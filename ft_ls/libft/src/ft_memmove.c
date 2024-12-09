

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_cp;
	const char	*src_cp;

	if (!dst && !src)
		return (NULL);
	dst_cp = (char *)dst;
	src_cp = (const char *)src;
	if (dst_cp > src_cp)
		while (len--)
			*(dst_cp + len) = *(src_cp + len);
	else
		while (len--)
			*dst_cp++ = *src_cp++;
	return (dst);
}
