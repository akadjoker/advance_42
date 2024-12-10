#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t strlen;
	char *p;
	char *substr;

	if (s == NULL)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	p = (char *)s + start;
	strlen = strlen - start;
	strlen = strlen < len ? strlen : len;
	substr = (char *)malloc((strlen + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, p, strlen + 1);
	return (substr);
}
