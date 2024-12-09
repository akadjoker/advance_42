#ifndef INCLUDE_H
#define INCLUDE_H

#include <elf.h>      // Elf64_Ehdr, Elf32_Ehdr, EI_CLASS,
#include <sys/stat.h> // stat, fstat()
#include <stdbool.h>  // bool type

#include <unistd.h> // write
#include <stdlib.h> // exit

#define PRINT_FILENAME(filename)   \
    {                              \
        write(1, "\n", 1);         \
        ft_putstr_fd(1, filename); \
        write(1, ":\n", 2);        \
    }

#define PRINT_SYMBOL_LINE(buffer, name) \
    ft_putstr_fd(1, buffer);            \
    ft_putstr_fd(1, name);              \
    write(1, "\n", 1)

#define PRINT_ERROR_OPENING_FILE(filename) \
    ft_putstr_fd(2, "ft_nm: '");           \
    ft_putstr_fd(2, filename);             \
    ft_putstr_fd(2, "': No such file\n");

#define PRINT_ERROR_IS_A_DIRECTORY(filename) \
    ft_putstr_fd(2, "ft_nm: Warning: '");    \
    ft_putstr_fd(2, filename);               \
    ft_putstr_fd(2, "' is a directory\n")

#define PRINT_ERROR_GET_FILE_SIZE() \
    ft_putstr_fd(2, "ft_nm: fstat : an error occured getting the file size\n");

#define PRINT_ERROR_MMAP_FAILED() \
    ft_putstr_fd(2, "ft_nm: mmap : an error occured mapping the file in the memory\n");

#define PRINT_ERROR_NO_SYMBOL_AND_EXIT(filename) \
    ft_putstr_fd(2, "ft_nm: ");                  \
    ft_putstr_fd(2, filename);                   \
    ft_putstr_fd(2, ": no symbols\n"), exit(0)

#define PRINT_ERROR_WRONG_FILE_FORMAT(filename) \
    ft_putstr_fd(2, "ft_nm: ");                 \
    ft_putstr_fd(2, filename);                  \
    ft_putstr_fd(2, ": file format not recognized\n")





#define SYMBOL_PADDING 3
#define PADDING_LEN_MAX 20
#define NO_FILE_ARG 0
#define FALSE 0
#define TRUE 1
#define END 0
#define UNDEFINED_SYMBOL '?'

#define SYMBOL_IS_LOCAL(elf) (ELF64_ST_BIND(elf.symbol_table->st_info) == STB_LOCAL)
#define SYMBOL_NAME(elf) (elf.strtab + elf.symbol_table->st_name)
#define SYMBOL_ADRESS(elf) (elf.symbol_table->st_value)
#define SECTION_HEADER(elf) (elf.symbol_table->st_shndx <= elf.header->e_shnum ? &elf.section_hdr[elf.symbol_table->st_shndx] : NULL)
#define SH_FLAG(section_hdr) (section_hdr->sh_flags)
#define SH_INDEX(symbol_table) (symbol_table->st_shndx)
#define SH_TYPE(symbol_table) (section_hdr->sh_type)
#define SYMBOL_IS_UNDEF(symbol) (symbol->symbol == 'U' || symbol->symbol == 'w' || symbol->symbol == 'v')
#define IS_LOCAL(c) (c >= 'a' && c <= 'z' && symbol != 'v' && symbol != 'w' && symbol != 'i') ? true : false

#define PRINT_ERROR_FILE_TOO_BIG(filename) \
    ft_putstr_fd(2, "ft_nm: '");           \
    ft_putstr_fd(2, filename);             \
    ft_putstr_fd(2, "': File too big\n")

#define PRINT_ERROR_CORRUPTED_FILE(filename) \
    ft_putstr_fd(2, "ft_nm: '");             \
    ft_putstr_fd(2, filename);               \
    ft_putstr_fd(2, "': Corrupted ELF file\n")

#define PRINT_ERROR_CORRUPTED_SECTIONS(filename) \
    ft_putstr_fd(2, "ft_nm: '");                 \
    ft_putstr_fd(2, filename);                   \
    ft_putstr_fd(2, "': Corrupted section headers\n")

#define PRINT_ERROR_SPECIAL_FILE(filename) \
    ft_putstr_fd(2, "ft_nm: '");           \
    ft_putstr_fd(2, filename);             \
    ft_putstr_fd(2, "': Not a regular file\n")

typedef struct s_file
{

    int fd;
    struct stat infos;
    char *file;
    char *filename;
} t_file;

typedef struct s_symbol
{

    int index;
    char *name;
    char symbol;
    uint64_t adress;
    struct s_symbol *next;
} t_symbol;

typedef struct s_options
{

    bool extern_only;
    bool undefined_only;
    bool reverse_sort;
    bool no_sort;
    bool help;
} t_options;

bool open_and_map_file(char *filename, t_file *file);

bool interpret_symbol_table_x64(t_file *file, t_options *options);

bool interpret_symbol_table_x32(t_file *file, t_options *options);

void add_symbol_to_lst(char *name, uint64_t adress, char symbol, t_symbol **lst, t_options *options);

void print_symbols_lst(t_symbol *lst, t_options *options,bool is64);
int ft_putnbr_base_len(unsigned long nbr, char *base);
void ft_putnbr_base(int nbr, char *base);
int ft_putstr(char *str);
int ft_putchar(int c);
int strcmp_no_case(char *s1, char *s2, bool opt_r);
void ft_putstr_fd(int fd, char *str);
void *ft_memset(void *s, int c, size_t n);
size_t ft_strlen(const char *str);
void *ft_memcpy(void *dest, const void *src, size_t n);
 char *ft_int_to_hex_str(int num);

#endif