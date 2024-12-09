

#include "libft.h"

void	ft_strdel(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}
