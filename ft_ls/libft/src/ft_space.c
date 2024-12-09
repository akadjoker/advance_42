

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (1);
	else if (c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

int	ft_isspacenl(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}