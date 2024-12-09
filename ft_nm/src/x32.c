#include "nm.h"

#define PADDING_LEN                          11
#define ST_TYPE(symbol_table)  (ELF32_ST_TYPE(symbol_table->st_info))
#define ST_BIND(symbol_table)  (ELF32_ST_BIND(symbol_table->st_info))
#define SYMBOL_TYPE(elf)       (ELF32_ST_TYPE(elf.symbol_table->st_info))



typedef struct s_elf
{
    Elf32_Ehdr *header;
    Elf32_Shdr *section_hdr;
    int symtab_index;
    Elf32_Sym *symbol_table;
    Elf32_Shdr *strtab_section;
    char *strtab;
    size_t symbols_nb;
} t_elf;

static char resolve_symbol_type(Elf32_Sym *symbol_table, Elf32_Shdr *section_hdr);
static bool symbol_is_data_section(Elf32_Sym *symbol_table, Elf32_Shdr *section_hdr);
static bool symbol_is_read_only_data_section(Elf32_Shdr *section_hdr);
static char resolve_undefined_symbol_type(Elf32_Sym *symbol_table);
static void init_elf_struct(t_file *file, t_elf *elf);
static int get_symtab_index(Elf32_Ehdr *elf_header, Elf32_Shdr *section_hdr_table);



 static bool is_valid_elf_header(const Elf32_Ehdr *header, size_t file_size)
{
    if (header->e_shoff >= file_size || header->e_phoff >= file_size)
        return false;

    size_t sh_size = (size_t)header->e_shnum * header->e_shentsize;
    if (sh_size > file_size - header->e_shoff)
        return false;

    if (header->e_shstrndx >= header->e_shnum)
        return false;

    if (header->e_shentsize < sizeof(Elf32_Shdr))
        return false;

    return true;
}

 static bool verify_section_headers(const t_file *file, const Elf32_Ehdr *ehdr)
{
    const Elf32_Shdr *shdr = (Elf32_Shdr *)(file->file + ehdr->e_shoff);

    if (shdr[0].sh_size != 0 || shdr[0].sh_offset != 0)
        return false;

    for (uint16_t i = 0; i < ehdr->e_shnum; i++)
    {
        if ((size_t)(shdr[i].sh_offset + shdr[i].sh_size) > (size_t)file->infos.st_size)
            return false;

        for (uint16_t j = i + 1; j < ehdr->e_shnum; j++)
        {
            if (shdr[i].sh_offset < shdr[j].sh_offset + shdr[j].sh_size &&
                shdr[j].sh_offset < shdr[i].sh_offset + shdr[i].sh_size)
                return false;
        }
    }
    return true;
}
bool interpret_symbol_table_x32(t_file *file, t_options *opt)
{
    static t_elf elf;
    char symbol;
    t_symbol *lst = NULL;

    init_elf_struct(file, &elf);


   if (!is_valid_elf_header(   elf.header, (size_t)file->infos.st_size))
    {
        PRINT_ERROR_WRONG_FILE_FORMAT(file->filename);
        return false;
    }

    if (!verify_section_headers(file, elf.header))
    {
         PRINT_ERROR_WRONG_FILE_FORMAT(file->filename);
        return false;
    }


    for (size_t j = 1; j < elf.symbols_nb; j++, elf.symbol_table++)
    {
        if (ELF32_ST_TYPE(elf.symbol_table->st_info) == STT_FILE || ELF32_ST_TYPE(elf.symbol_table->st_info) == STT_SECTION)
            continue;
        else if (opt->undefined_only)
        {
            symbol = resolve_undefined_symbol_type(elf.symbol_table);
            if (symbol != UNDEFINED_SYMBOL)
                add_symbol_to_lst(SYMBOL_NAME(elf), SYMBOL_ADRESS(elf), symbol, &lst, opt);
        }
        else
        {
            symbol = resolve_symbol_type(elf.symbol_table, SECTION_HEADER(elf));
            if (ELF32_ST_BIND(elf.symbol_table->st_info) == STB_LOCAL && symbol != UNDEFINED_SYMBOL)
                symbol += 32;
            add_symbol_to_lst(SYMBOL_NAME(elf), SYMBOL_ADRESS(elf), symbol, &lst, opt);
        }
    }
    print_symbols_lst(lst, opt,0);
    return true;
}

static char resolve_symbol_type(Elf32_Sym *symbol_table, Elf32_Shdr *section_hdr)
{
    if (ELF32_ST_TYPE(symbol_table->st_info) == STT_GNU_IFUNC)
        return 'i';
    else if (ELF32_ST_BIND(symbol_table->st_info) == STB_WEAK)
    {
        if (ELF32_ST_TYPE(symbol_table->st_info) == STT_OBJECT)
            return symbol_table->st_shndx == SHN_UNDEF ? 'v' : 'V';
        return symbol_table->st_shndx == SHN_UNDEF ? 'w' : 'W';
    }
    else if (section_hdr && (section_hdr->sh_type == SHT_PROGBITS) &&
             (section_hdr->sh_flags == (SHF_ALLOC | SHF_EXECINSTR) ||
              section_hdr->sh_flags == (SHF_ALLOC | SHF_EXECINSTR | SHF_GROUP)))
        return 'T';
    else if (symbol_table->st_shndx == SHN_UNDEF)
        return 'U';
    else if (symbol_is_read_only_data_section(section_hdr))
        return 'R';
    else if (symbol_is_data_section(symbol_table, section_hdr))
        return section_hdr->sh_type == SHT_NOBITS ? 'B' : 'D';
    else if (ELF32_ST_BIND(symbol_table->st_info) == STB_GNU_UNIQUE)
        return 'u';
    else if (symbol_table->st_shndx == SHN_ABS)
        return 'A';
    else if (symbol_table->st_shndx == SHN_COMMON)
        return 'C';

    return '?';
}

static bool symbol_is_data_section(Elf32_Sym *symbol_table, Elf32_Shdr *section_hdr)
{
    if (!section_hdr)
        return false;

    if (ELF32_ST_TYPE(symbol_table->st_info) == STT_OBJECT)
        return true;
    else if (ELF32_ST_TYPE(symbol_table->st_info) == STT_NOTYPE)
        return true;
    else if (section_hdr->sh_type == SHT_INIT_ARRAY)
        return true;
    else if (section_hdr->sh_type == SHT_FINI_ARRAY)
        return true;
    else if (section_hdr->sh_type == SHT_DYNAMIC)
        return true;
    else if (section_hdr->sh_flags == SHT_SHLIB)
        return true;
    else if (section_hdr->sh_flags == (SHF_ALLOC | SHF_WRITE | SHF_TLS))
        return true;

    return false;
}

static bool symbol_is_read_only_data_section(Elf32_Shdr *section_hdr)
{
    if (!section_hdr)
        return false;

    if (section_hdr->sh_type == SHT_REL)
        return true;
    else if (section_hdr->sh_type == SHT_RELA)
        return true;
    else if (section_hdr->sh_type == SHT_NOTE)
        return true;
    else if ((section_hdr->sh_flags & SHF_STRINGS) > 0)
        return true;
    else if (section_hdr->sh_type == SHT_PROGBITS && (section_hdr->sh_flags == SHF_ALLOC ||
                                                      section_hdr->sh_flags == (SHF_ALLOC | SHF_MERGE)))
        return true;

    return false;
}

static char resolve_undefined_symbol_type(Elf32_Sym *symbol_table)
{
    if (ELF32_ST_BIND(symbol_table->st_info) == STB_WEAK)
    {
        if (ELF32_ST_TYPE(symbol_table->st_info) == STT_OBJECT)
            return symbol_table->st_shndx == SHN_UNDEF ? 'v' : '?';
        return symbol_table->st_shndx == SHN_UNDEF ? 'w' : '?';
    }
    else if (symbol_table->st_shndx == SHN_UNDEF)
        return 'U';

    return '?';
}

static void init_elf_struct(t_file *file, t_elf *elf)
{
    ft_memset(elf, 0, sizeof(t_elf));

    elf->header = (Elf32_Ehdr *)file->file;
    elf->section_hdr = (Elf32_Shdr *)&file->file[elf->header->e_shoff];
    elf->symtab_index = get_symtab_index(elf->header, elf->section_hdr);

    if (elf->symtab_index == -1)
    {
        PRINT_ERROR_NO_SYMBOL_AND_EXIT(file->filename);
    }

    elf->symbol_table = (Elf32_Sym *)(file->file + elf->section_hdr[elf->symtab_index].sh_offset);
    elf->strtab_section = &elf->section_hdr[elf->section_hdr[elf->symtab_index].sh_link];
    elf->strtab = (char *)(file->file + elf->strtab_section->sh_offset);
    elf->symbols_nb = elf->section_hdr[elf->symtab_index].sh_size / sizeof(Elf32_Sym);
    elf->symbol_table++;
}

static int get_symtab_index(Elf32_Ehdr *elf_header, Elf32_Shdr *section_hdr_table)
{
    for (int i = 0; i < elf_header->e_shnum; i++)
    {
        if (section_hdr_table[i].sh_type == SHT_SYMTAB)
        {
            return i;
        }
    }
    return -1;
}