

#include "internal.h"

EXPORT void *realloc(void *ptr, size_t size)
{
    ft_lock();
    debug_hex("[*] realloc(", ptr, "");
    debug_var(", size(", size, ")\n");
    void *ret = ft_realloc(ptr, size);
    debug_hex("[-] ret realloc ", ret, "\n");
    ft_unlock();
    return ret;
}
