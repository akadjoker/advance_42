
#include "internal.h"



EXPORT void *malloc(size_t size)
{
    ft_lock();
    debug_var("[*] malloc(", size, ")\n");
    void *ret = ft_malloc(size);
    debug_hex("[-]  malloc ", ret, "\n");
    ft_unlock();
    return ret;
}