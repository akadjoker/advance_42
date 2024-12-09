
#include <signal.h>
#include "internal.h"
#include "ft_malloc.h"


__attribute__((constructor))
static void mallocstart(void) 
{


    if (!g_zone.init)
    {
        isDebug();
        g_zone.init = true;
    }
    debug_str("=== FT Malloc initialized ===\n");
 
}

__attribute__((destructor, used))
static void mallocend(void) 
{
    debug_str("=== FT Malloc destroyed ===\n");
    //free_all_zones();// n EALIDADE NAO FAZ FALTA , MAS , EU QUERO
    if (isDebug() &&  g_zone.size)
    {
        show_alloc_mem();
    }
    g_zone.size=0;
}
