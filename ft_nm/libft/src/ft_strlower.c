#include "libft.h"

void ft_strlower(char *str)
{
	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
}
