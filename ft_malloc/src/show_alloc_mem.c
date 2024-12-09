

#include "internal.h"


void set_red()
{
    ft_putstr("\033[31m");
}

void set_green()
{
    ft_putstr("\033[32m");
}

void set_yellow()
{
    ft_putstr("\033[33m");
}

void set_blue()
{
    ft_putstr("\033[34m");
}

void set_normal()
{
    ft_putstr("\033[0m");
}

void puthex(unsigned long long int hex, int min)
{
    char str[23];
    char strHex[] = "0123456789ABCDEF";
    int index = 23;


    ft_memset(str, '0', 23);
    while (hex)
    {
        index--;
        str[index] = strHex[hex % 16];
        hex /= 16;
    }
    if (23 - index > min)
    {
         write(1, &str[index], 23 - index);
    }
    else
    {
        write(1, &str[23 - min], min);
    }

}

void debug_str(char *str)
{
    if (MALLOC_DEBUG && isDebug())
    {
        set_blue();
        ft_putstr(str);
        set_normal();
    }
}

void debug_var(char *name, long long int var, char *end)
{
    if (MALLOC_DEBUG && isDebug())
    {
        set_green();
        ft_putstr(name);
        ft_putnbr(var);
        ft_putstr(end);
        set_normal();
    }
}

void debug_hex(char *name, void *var, char *end)
{
    if (MALLOC_DEBUG && isDebug())
    {
        set_yellow();
        ft_putstr(name);
        ft_putstr("0x");
        puthex((uintptr_t)var, 8);
        ft_putstr(end);
        set_normal();
   
    }
}


void print_range(t_block *block, char *start, char *end)
{
    ft_putstr("0x");
    ft_itoa_base((size_t)start, 16);
    ft_putstr(" - ");
    ft_putstr("0x");
    ft_itoa_base((size_t)end, 16);
    ft_putstr(" : ");
    ft_itoa_base(block->size, 10);
    ft_putstr(" bytes\n");
}


static void print_block(t_block *block, size_t sizeZone, size_t *total)
{
   
    if (sizeZone <= 0 || !block)
    {
        return;
    }
    if (!block->free)
    {

            void *start = (char *)block + sizeof(t_block);
            void *end   = (char *)start + block->size;
            ft_putaddr(start);
            ft_putstr(" - ");
            ft_putaddr(end);
            ft_putstr(" : ");
            ft_putnbr(block->size);
            ft_putstr(" bytes\n");

       
            *total += block->size;
    }
   
    return print_block(getNextBlock(block), sizeZone - (sizeof(t_block) + block->size), total);
}



EXPORT void show_alloc_mem(void)
{
     ft_lock();
    size_t total = 0;
    if (g_zone.size==0) return;
   
    for (unsigned int index = 0; index < g_zone.size; index++)
    {

        if (g_zone.zones[index])
        {
            char *type_str;
                switch (g_zone.zones[index]->type)
                {
                    case tiny:
                        type_str = "TINY";
                    break;
                    case small:
                        type_str = "SMALL";
                    break;
                    default:
                        type_str = "LARGE";
                    break;
                }

            set_blue();
            ft_putstr(type_str);
            ft_putstr(" : ");
            ft_putaddr(g_zone.zones[index]);
            ft_putchar('\n');
            set_yellow();
            print_block(getFirstBlock(g_zone.zones[index]),g_zone.zones[index]->size,&total);

        }
    }
    set_green();
    ft_putstr("Total : ");
    ft_putnbr(total);
    ft_putstr(" bytes\n");
    set_normal();
    ft_unlock();
}