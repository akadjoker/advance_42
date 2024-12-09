

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		*s_cp;
	char		d;

	s_cp = (char *)s;
	d = (char)c;
	while (*s_cp != d)
		if (!*s_cp++)
			return (NULL);
	return (s_cp);
}
