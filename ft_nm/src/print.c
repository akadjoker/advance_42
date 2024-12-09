#include "nm.h"
#include <stdlib.h> // malloc()



static void print_lst(t_symbol *lst,bool is64);
static void recursive_print_lst(t_symbol *lst,bool is64);


static int get_size_addr(bool is64)
{
    if (is64)
        return 16;
    else
        return 8;
}

static void print_chars(int c, int size)
{
    for (int i = 0; i < size; i++)
        ft_putchar(c);
}


void print_symbols_lst(t_symbol *lst, t_options *options,bool is64)
{

    if (options->reverse_sort & !options->no_sort)
        recursive_print_lst(lst,is64);
    else
        print_lst(lst,is64);
    lst = NULL;
}

static void print_lst(t_symbol *lst,bool is64)
{

    t_symbol *symbol = lst;
    t_symbol *node_to_free = NULL;

    while (symbol)
    {

        if (SYMBOL_IS_UNDEF(symbol))
        {
            print_chars(' ', get_size_addr(is64));

        }else 
        {
            unsigned long addr = symbol->adress;
            int len = get_size_addr(is64) - ft_putnbr_base_len((unsigned long)(addr & 0xFFFFFFFF), "0123456789abcdef");
            print_chars('0', len);
            ft_putnbr_base((unsigned long)(addr & 0xFFFFFFFF), "0123456789abcdef");
        }




        ft_putchar(' ');
        ft_putchar(symbol->symbol);
        ft_putchar(' ');
        ft_putstr(symbol->name);
        ft_putchar('\n');



        node_to_free = symbol;
        symbol = symbol->next;
        free(node_to_free);
        node_to_free = NULL;
    }
}

static void recursive_print_lst(t_symbol *lst,bool is64)
{

    t_symbol *symbol = lst;


    if (symbol->next)
        recursive_print_lst(symbol->next,is64);

    if (SYMBOL_IS_UNDEF(symbol))
    {
        print_chars(' ', get_size_addr(is64));

    }else 
    {
        unsigned long addr = symbol->adress;
        int len = get_size_addr(is64) - ft_putnbr_base_len((unsigned long)(addr & 0xFFFFFFFF), "0123456789abcdef");
        print_chars('0', len);
        ft_putnbr_base((unsigned long)(addr & 0xFFFFFFFF), "0123456789abcdef");
    }


    ft_putchar(' ');
    ft_putchar(symbol->symbol);
    ft_putchar(' ');
    ft_putstr(symbol->name);
    ft_putchar('\n');


    free(symbol);
    symbol = NULL;
}
