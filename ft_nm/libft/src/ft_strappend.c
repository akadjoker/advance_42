#include "libft.h"

char *ft_strappend(char *dest, char const *src)
{
	char *res;

	res = ft_strjoin(dest, src);
	free(dest);
	return res;
}
