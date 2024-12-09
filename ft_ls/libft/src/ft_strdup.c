

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	dup = ft_strnew(ft_strlen(s1));
	if (!dup)
		return (NULL);
	i = 0;
	while (*s1)
		dup[i++] = *s1++;
	return (dup);
}
