#include "internal.h"



void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (!dest && !src)
        return NULL;

    while (n--)
        *d++ = *s++;

    return dest;
}
size_t ft_strlen(const char *str)
{

    if (!str)
        return (0);

    size_t i = 0;
    while (str[i])
        i++;

    return (i);
}

int ft_putchar(int c) { return (write(1, &c, 1)); }





char *ft_strncpy(char *dst, const char *src, size_t len)
{
    char *ret;

    if (!dst || !src)
        return (dst);
        
    ret = dst;
    while (len > 0)
    {
        len--;
        if (*src)
            *dst++ = *src++;
        else
            *dst++ = '\0';
    }
    
    return (ret);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (s1 - s2);
	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_cpy;
	unsigned char	d;

	d = (unsigned char)c;
	b_cpy = (unsigned char *)b;
	while (len--)
		*b_cpy++ = d;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void ft_putstr(char const *s)
{
    int i;

    i = 0;
    if (!s)
        return;
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
}

void	ft_putnbr(int n)
{
	long	nbr;
	char	c;

	nbr = n;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr / 10 > 0)
		ft_putnbr(nbr / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}


static int	pf_abs(int nbr)
{
	return (nbr < 0 ? -nbr : nbr);
}

static void	ft_aux(long long int val, int base, char **p)
{
	char	*base_str;
	int		tmp;

	base_str = "0123456789ABCDEF";
	if (val >= base || val <= -base)
		ft_aux(val / base, base, p);
	tmp = (int)(val % base);
	*(*p)++ = *(base_str + pf_abs(tmp));
}

void		ft_itoa_base(long long int value, int base)
{
	char	*p;
    char    res[100];

    ft_bzero(res, 100);
	if (base < 2 || base > 16)
		return ;
	p = res;
	if (value < 0 && base == 10)
		*p++ = '-';
	ft_aux(value, base, &p);
	*p = 0;
    ft_putstr(res);
}

void ft_putnbr_base(size_t nbr, char *base, int base_len)
{
	if (nbr >= (size_t)base_len)
	{
		ft_putnbr_base(nbr / base_len, base, base_len);
		ft_putnbr_base(nbr % base_len, base, base_len);
	}
	else
	{
		ft_putchar(base[nbr]);
	}
}

void ft_putaddr(void *ptr)
{
	ft_putstr("0x");
	ft_putnbr_base((size_t)ptr, "0123456789ABCDEF", 16);
}