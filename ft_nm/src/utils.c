#include "nm.h"
#include <unistd.h> // write()

static bool ft_isalnum(int c);
static bool is_upper(char c);
static int strcmp_case(char *s1, char *s2, bool opt_r);

int strcmp_no_case(char *s1, char *s2, bool opt_r)
{

    size_t i = 0, j = 0, _s1 = 0, _s2 = 0;

    for (; s1[i] || s2[j]; i++, j++)
    {

        for (; (s1[i] && !ft_isalnum(s1[i])); i++, _s1++)
            ;
        for (; (s2[j] && !ft_isalnum(s2[j])); j++, _s2++)
            ;

        if (!s1[i] && !s2[j])
            return ((opt_r) ? 1 : 0);
        if (!s1[i])
            return -1;
        if (!s2[j])
            return 1;

        char c1 = s1[i];
        char c2 = s2[j];

        is_upper(c1) ? c1 += 32 : c1;
        is_upper(c2) ? c2 += 32 : c2;
        if (c1 != c2)
            return (unsigned char)c1 - (unsigned char)c2;
    }
    return (strcmp_case(s1, s2, opt_r));
}

static int strcmp_case(char *s1, char *s2, bool opt_r)
{

    int i = 0, j = 0;

    for (; s1[i] && s2[j]; i++, j++)
    {

        for (; (s1[i] && !ft_isalnum(s1[i])); i++)
            ;
        for (; (s2[j] && !ft_isalnum(s2[j])); j++)
            ;
        if (i < j || s1[i] < s2[j])
            return 1;
        else if (i > j || s1[i] > s2[j])
            return 0;
    }
    return ((opt_r) ? 1 : 0);
}

static bool ft_isalnum(int c)
{

    if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
        return TRUE;
    else
        return FALSE;
}

static bool is_upper(char c)
{
    if (c >= 'A' && c <= 'Z')
        return true;
    return false;
}

void ft_putstr_fd(int fd, char *str)
{

    if (fd < 0 || !str)
        return;
    write(fd, str, ft_strlen(str));
}

void *ft_memset(void *s, int c, size_t n)
{

    char *str = s;

    str = s;
    for (size_t i = 0; i < n; i++)
    {
        str[i] = c;
    }
    return (s);
}

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


static int ft_sort_int_tab(char *str)
{
    int i;
    int m;

    i = 0;
    while (str[i])
    {
        m = i + 1;
        while (str[m])
        {
            if (str[i] == str[m])
                return (0);
            ++m;
        }
        ++i;
    }
    return (1);
}

int ft_putchar(int c) { return (write(1, &c, 1)); }


int ft_putstr(char *str)
{
    size_t res;

    if (!str)
        return (0);
    res = 0;
    while (*str)
    {
        res += ft_putchar(*str);
        str++;
    }
    return (res);
}

void ft_putnbr_base(int nbr, char *base)
{
    unsigned int lnbr;
    unsigned int size;

    lnbr = nbr;
    size = ft_strlen(base);
    if (size <= 1)
        return;
    if (!ft_sort_int_tab(base))
        return;
    if (nbr < 0)
    {
        ft_putchar('-');
        lnbr *= -1;
    }
    if (lnbr / size)
    {
        ft_putnbr_base(lnbr / size, base);
        ft_putchar(base[lnbr % size]);
    }
    else
        ft_putchar(base[lnbr % size]);
}

int ft_putnbr_base_len(unsigned long nbr, char *base)
{
    int len = 0;
    unsigned int size = ft_strlen(base);

    if (size <= 1)
        return (0);
    if (!ft_sort_int_tab(base))
        return (0);

    if (nbr == 0)
        return (1);

    while (nbr)
    {
        len++;
        nbr /= size;
    }

    return (len);
}