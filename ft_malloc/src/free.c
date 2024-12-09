
#include "internal.h"



EXPORT void free(void *ptr)
{
    ft_lock();
    debug_hex("[*] free(", ptr, ")\n");
    ft_free(ptr);
    debug_str("[-] ret free\n");
    ft_unlock();
}