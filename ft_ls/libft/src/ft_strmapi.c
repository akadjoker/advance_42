

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*strmap;

	if (!s || !f)
		return (NULL);
	strmap = (char *)malloc(sizeof(*strmap) * (ft_strlen(s) + 1));
	if (!(strmap))
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		strmap[i] = (*f)(i, s[i]);
	strmap[i] = '\0';
	return (strmap);
}
