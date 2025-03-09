#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    if (!s)
        return 0;
    while (s[len])
        len++;
    return len;
}

char *ft_strcpy(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_strdup(const char *s)
{
    if (!s)
        return NULL;
    size_t len = ft_strlen(s);
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    return ft_strcpy(copy, s);
}

int ft_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

char *ft_strcat(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;
    char *ptr = dest + ft_strlen(dest);
    while (*src)
        *ptr++ = *src++;
    *ptr = '\0';
    return dest;
}

void ft_itoa(long long num, char *buffer)
{
    int i = 0;
    int is_negative = (num < 0);

    if (num == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (is_negative)
        num = -num;

    while (num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative)
        buffer[i++] = '-';

    buffer[i] = '\0';

    // Inverter a string
    int start = 0, end = i - 1;
    while (start < end)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

void ft_print_str(const char *str)
{
    if (!str)
        return;
    write(1, str, ft_strlen(str));
}

void ft_join_path(char *buffer, size_t size, const char *path, const char *name)
{
    size_t path_len = ft_strlen(path);
    size_t name_len = ft_strlen(name);

    if (path_len + name_len + 2 > size) // +2 para '/' e '\0'
        return;

    ft_strcpy(buffer, path);

    if (path[path_len - 1] != '/')
    {
        buffer[path_len] = '/';
        buffer[path_len + 1] = '\0';
    }

    ft_strcat(buffer, name);
}

void ft_error_str(const char *str, const char *err, int nl)
{
    ft_print_str(str);
    ft_print_str(err);
    if (nl)
        write(1, "\n", 1);
}

char *ft_strnew(size_t size)
{
    char *str = malloc(size + 1);
    if (!str)
        return NULL;
        
    for (size_t i = 0; i <= size; i++)
        str[i] = '\0';
        
    return str;
}

char *ft_strjoin(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return NULL;
        
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    
    char *result = ft_strnew(len1 + len2);
    if (!result)
        return NULL;
        
    ft_strcpy(result, s1);
    ft_strcat(result, s2);
    
    return result;
}

char *ft_strsub(const char *s, unsigned int start, size_t len)
{
    if (!s)
        return NULL;
        
    char *result = ft_strnew(len);
    if (!result)
        return NULL;
        
    for (size_t i = 0; i < len; i++)
        result[i] = s[start + i];
        
    return result;
}

char *ft_strncpy(char *dst, const char *src, size_t len)
{
    size_t i;
    
    for (i = 0; i < len && src[i]; i++)
        dst[i] = src[i];
        
    while (i < len)
        dst[i++] = '\0';
        
    return dst;
}
