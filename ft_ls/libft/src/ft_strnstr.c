

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0 || needle == haystack)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] && len - i >= needle_len)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char*)haystack + i);
		i++;
	}
	return (NULL);
}

char *ft_strstr(const char *haystack, const char *needle)
{
    size_t i;
    size_t j;

    if (!needle[0])
        return ((char *)haystack);

    i = 0;
    while (haystack[i])
    {
        j = 0;
        while (needle[j] && haystack[i + j] == needle[j])
            j++;
        if (!needle[j])
            return ((char *)&haystack[i]);
        i++;
    }
    return (NULL);
}