#include "internal.h"



EXPORT void *calloc(size_t nmemb, size_t size)
{
    ft_lock();
    debug_var("[*] calloc(", nmemb,"");
    debug_var(", size(", size,") )\n");
    void *ret = ft_calloc(nmemb, size);
    debug_hex("[-] ret calloc ", ret, "\n");
    ft_unlock();
    return ret;
}