

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1_cp;
	const unsigned char	*s2_cp;

	s1_cp = (const unsigned char *)s1;
	s2_cp = (const unsigned char *)s2;
	while (n--)
	{
		if (!*s1_cp || !*s2_cp)
			return (*s1_cp - *s2_cp);
		if (*s1_cp++ != *s2_cp++)
			return (*--s1_cp - *--s2_cp);
	}
	return (0);
}
