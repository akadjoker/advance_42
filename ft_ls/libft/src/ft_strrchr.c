

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		s_len;
	char	*s_cp;
	char	d;

	s_len = ft_strlen(s) + 1;
	s_cp = (char *)s;
	d = (char)c;
	while (s_len--)
		if (*(s_cp + s_len) == d)
			return (s_cp + s_len);
	return (NULL);
}
