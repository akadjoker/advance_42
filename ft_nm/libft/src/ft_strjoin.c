#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	size_t len;
	char *result;

	if (s1 == NULL || s2 == NULL)
		return NULL;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(len * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len);
	ft_strlcat(result, s2, len);
	return (result);
}