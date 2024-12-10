#include "ft_nm.h"

static const Elf64_Shdr *find_section_type_64(
    const Elf64_Shdr *shdrtab,
    size_t shdrtab_size,
    uint32_t sh_type)
{
    for (size_t i = 0; i < shdrtab_size; ++i)
    {
        if (shdrtab[i].sh_type == sh_type)
            return &shdrtab[i];
    }
    return NULL;
}

static struct s_symbol *parse_sym_64(
    const Elf64_Sym *sym,
    const char *strtab,
    const Elf64_Shdr *shdrtab,
    const char *shstrtab)
{
    struct s_symbol *symbol;

    symbol = (struct s_symbol *)malloc(sizeof(struct s_symbol));
    symbol->ei_class = 2; // 64-bit
    symbol->st_name = ft_strdup(&strtab[sym->st_name]);
    symbol->st_bind = ELF64_ST_BIND(sym->st_info);
    symbol->st_type = ELF64_ST_TYPE(sym->st_info);
    symbol->st_value = sym->st_value;
    symbol->st_shndx = sym->st_shndx;

    if (sym->st_shndx != SHN_ABS)
    {
        const Elf64_Shdr *shdr = &shdrtab[sym->st_shndx];
        symbol->sh_type = shdr->sh_type;
        symbol->sh_name = ft_strdup(&shstrtab[shdr->sh_name]);
        symbol->sh_flags = shdr->sh_flags;
    }
    else
    {
        symbol->sh_type = SHT_NULL;
        symbol->sh_name = ft_strdup("");
        symbol->sh_flags = 0;
    }
    return symbol;
}

static t_list *get_sym_list_64(
    const Elf64_Sym *symtab,
    size_t symtab_size,
    const char *strtab,
    const Elf64_Shdr *shdrtab,
    const char *shstrtab)
{
    t_list *list;
    struct s_symbol *sym;

    list = NULL;
    for (size_t i = 0; i < symtab_size; ++i)
    {
        sym = parse_sym_64(&symtab[i], strtab, shdrtab, shstrtab);
        if (sym->st_name[0] != '\0' && sym->st_shndx != SHN_ABS)
            ft_lstadd_front(&list, ft_lstnew(sym));
        else
            free_symbol(sym);
    }
    return list;
}

// Main parse function for 64-bit ELF
t_list *parse_64(const char *ptr, char *path, struct stat s)
{
    const Elf64_Ehdr *ehdr;
    const Elf64_Shdr *shdrtab;
    size_t shdrtab_size;
    const Elf64_Shdr *symtab_shdr;
    const Elf64_Sym *symtab;
    size_t symtab_size;
    const Elf64_Shdr *strtab_shdr;
    const char *strtab;
    const Elf64_Shdr *shstrtab_shdr;
    const char *shstrtab;
    t_list *sym_list;

    ehdr = (Elf64_Ehdr *)ptr;
    shdrtab = (Elf64_Shdr *)&ptr[ehdr->e_shoff];
    shdrtab_size = ehdr->e_shnum;

    if (ehdr->e_shoff > (long unsigned int)s.st_size ||
        ehdr->e_shoff + shdrtab_size * ehdr->e_shentsize > (long unsigned int)s.st_size)
    {
        print_error("file too short", path);
        return NULL;
    }

    symtab_shdr = find_section_type_64(shdrtab, shdrtab_size, SHT_SYMTAB);
    if (!symtab_shdr)
        return NULL;

    symtab = (Elf64_Sym *)&ptr[symtab_shdr->sh_offset];
    symtab_size = symtab_shdr->sh_size / symtab_shdr->sh_entsize;
    strtab_shdr = &shdrtab[symtab_shdr->sh_link];
    strtab = &ptr[strtab_shdr->sh_offset];
    shstrtab_shdr = &shdrtab[ehdr->e_shstrndx];
    shstrtab = &ptr[shstrtab_shdr->sh_offset];

    sym_list = get_sym_list_64(symtab, symtab_size, strtab, shdrtab, shstrtab);
    return sym_list;
}