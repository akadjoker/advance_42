#include "ft_nm.h"

/**
 * Finds a section header of a specified type within a table of section headers.
 * 
 * This function iterates through a given section header table and searches
 * for a section header that matches the specified section type. If a matching
 * section header is found, a pointer to it is returned. If no matching section
 * header is found, the function returns NULL.
 * 
 * @param shdrtab Pointer to the start of the section header table.
 * @param shdrtab_size The number of section headers in the table.
 * @param sh_type The type of the section header to find.
 * 
 * @return A pointer to the matching section header if found, or NULL if no
 *         matching section header is found.
 */
static const Elf32_Shdr *find_section_type_32(const Elf32_Shdr *shdrtab,size_t shdrtab_size,uint32_t sh_type)
{
    for (size_t i = 0; i < shdrtab_size; ++i)
    {
        if (shdrtab[i].sh_type == sh_type)
            return &shdrtab[i];
    }
    return NULL;
}

/**
 * Parses a 32-bit ELF symbol table entry.
 *
 * This function takes a pointer to a symbol table entry, a string table, a
 * section header table, and a section header string table. It returns a pointer
 * to a struct s_symbol, which is a parsed version of the symbol table entry.
 *
 * The fields of the returned struct s_symbol are set as follows:
 * - ei_class is set to 1, indicating a 32-bit ELF file.
 * - st_name is set to a string containing the name of the symbol.
 * - st_bind and st_type are set to the binding and type of the symbol,
 *   respectively.
 * - st_value is set to the value of the symbol.
 * - st_shndx is set to the index of the section containing the symbol.
 * - If the symbol is not absolute (i.e. it is not in section SHN_ABS), then
 *   sh_type is set to the type of the section containing the symbol, sh_name is
 *   set to the name of the section, and sh_flags is set to the flags of the
 *   section. If the symbol is absolute, then sh_type is set to SHT_NULL,
 *   sh_name is set to an empty string, and sh_flags is set to 0.
 *
 * @param[in] sym A pointer to the symbol table entry to parse.
 * @param[in] strtab A pointer to the string table containing the symbol names.
 * @param[in] shdrtab A pointer to the section header table.
 * @param[in] shstrtab A pointer to the section header string table.
 *
 * @return A pointer to a struct s_symbol containing the parsed symbol
 *         information.
 */
static struct s_symbol *parse_sym_32(
    const Elf32_Sym *sym,
    const char *strtab,
    const Elf32_Shdr *shdrtab,
    const char *shstrtab)
{
    struct s_symbol *symbol;

    symbol = (struct s_symbol *)malloc(sizeof(struct s_symbol));
    symbol->ei_class = 1; // 32-bit
    symbol->st_name = ft_strdup(&strtab[sym->st_name]);
    symbol->st_bind = ELF32_ST_BIND(sym->st_info);
    symbol->st_type = ELF32_ST_TYPE(sym->st_info);
    symbol->st_value = sym->st_value;
    symbol->st_shndx = sym->st_shndx;

    if (sym->st_shndx != SHN_ABS)
    {
        const Elf32_Shdr *shdr = &shdrtab[sym->st_shndx];
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

/**
 * Creates a linked list of symbols from a 32-bit ELF symbol table.
 *
 * This function takes a pointer to a symbol table, a string table, a section
 * header table, and a section header string table. It returns a pointer to a
 * linked list of struct s_symbol, which is a parsed version of the symbol
 * table entries that are not absolute.
 *
 * The list is sorted in-place, and the function does not return anything.
 *
 * @param[in] symtab A pointer to the symbol table.
 * @param[in] symtab_size The size of the symbol table.
 * @param[in] strtab A pointer to the string table containing the symbol names.
 * @param[in] shdrtab A pointer to the section header table.
 * @param[in] shstrtab A pointer to the section header string table.
 *
 * @return A pointer to a linked list of struct s_symbol containing the parsed
 *         symbols.
 */
static t_list *get_sym_list_32(
    const Elf32_Sym *symtab,
    size_t symtab_size,
    const char *strtab,
    const Elf32_Shdr *shdrtab,
    const char *shstrtab)
{
    t_list *list;
    struct s_symbol *sym;

    list = NULL;
    for (size_t i = 0; i < symtab_size; ++i)
    {
        sym = parse_sym_32(&symtab[i], strtab, shdrtab, shstrtab);
        if (sym->st_name[0] != '\0' && sym->st_shndx != SHN_ABS)
            ft_lstadd_front(&list, ft_lstnew(sym));
        else
            free_symbol(sym);
    }
    return list;
}


/**
 * Parses a 32-bit ELF file and returns a list of symbols.
 *
 * This function takes a pointer to an ELF file, a string containing the path
 * to the file, and a struct stat containing information about the file. It
 * parses the ELF file, and returns a linked list of struct s_symbol containing
 * the symbols in the file.
 *
 * The function checks that the file is a valid ELF file, and that it is not
 * corrupted. If the file is invalid or corrupted, the function prints an
 * error message to the standard error output, and returns NULL.
 *
 * @param[in] ptr A pointer to the ELF file.
 * @param[in] path A string containing the path to the file.
 * @param[in] s A struct stat containing information about the file.
 *
 * @return A linked list of struct s_symbol containing the symbols in the file,
 *         or NULL if an error occurs.
 */
t_list *parse_32(const char *ptr, char *path, struct stat s)
{
    const Elf32_Ehdr *ehdr;
    const Elf32_Shdr *shdrtab;
    size_t shdrtab_size;
    const Elf32_Shdr *symtab_shdr;
    const Elf32_Sym *symtab;
    size_t symtab_size;
    const Elf32_Shdr *strtab_shdr;
    const char *strtab;
    const Elf32_Shdr *shstrtab_shdr;
    const char *shstrtab;
    t_list *sym_list;

    ehdr = (Elf32_Ehdr *)ptr;
    shdrtab = (Elf32_Shdr *)&ptr[ehdr->e_shoff];
    shdrtab_size = ehdr->e_shnum;

    if (ehdr->e_shoff > (long unsigned int)s.st_size ||
        ehdr->e_shoff + shdrtab_size * ehdr->e_shentsize > (long unsigned int)s.st_size)
    {
        print_error("file too short", path);
        return NULL;
    }

    symtab_shdr = find_section_type_32(shdrtab, shdrtab_size, SHT_SYMTAB);
    if (!symtab_shdr)
        return NULL;

    symtab = (Elf32_Sym *)&ptr[symtab_shdr->sh_offset];
    symtab_size = symtab_shdr->sh_size / symtab_shdr->sh_entsize;
    strtab_shdr = &shdrtab[symtab_shdr->sh_link];
    strtab = &ptr[strtab_shdr->sh_offset];
    shstrtab_shdr = &shdrtab[ehdr->e_shstrndx];
    shstrtab = &ptr[shstrtab_shdr->sh_offset];

    sym_list = get_sym_list_32(symtab, symtab_size, strtab, shdrtab, shstrtab);
    return sym_list;
}