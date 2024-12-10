#include "ft_nm.h"

// https://github.com/bminor/binutils-gdb/blob/master/binutils/nm.c

// Os símbolos weak ('w')
// Os símbolos undefined ('U')
// Os símbolos de texto ('t', 'T')
// Os símbolos de dados ('d', 'D')
// Os símbolos read-only ('r', 'R')
// Os símbolos BSS ('b', 'B')


static struct s_sym_type_ref symbol_type_ref[] =
	{
		{
			.st_bind = STB_WEAK,
			.st_type = STT_OBJECT,
			.st_value = -1,
			.st_shndx = SHN_UNDEF,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'v',
		},
		{
			.st_bind = STB_WEAK,
			.st_type = STT_OBJECT,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'V',
		},
		{
			.st_bind = STB_WEAK,
			.st_type = -1,
			.st_shndx = SHN_UNDEF,
			.st_value = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'w',
		},
		{
			.st_bind = STB_WEAK,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'W',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_NOBITS,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'b',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_NOBITS,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'B',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = 0,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'u',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = 0,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'U',
		},
		{
			.st_bind = -1,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = SHF_WRITE,
			.sh_name = ".group",
			.letter = 'n',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".text",
			.letter = 't',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".text",
			.letter = 'T',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".exit.text",
			.letter = 't',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".exit.text",
			.letter = 'T',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".init.text",
			.letter = 't',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".init.text",
			.letter = 'T',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".init",
			.letter = 't',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".init",
			.letter = 'T',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".fini",
			.letter = 't',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = ".fini",
			.letter = 'T',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = SHF_WRITE,
			.sh_name = "",
			.letter = 'r',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = -1,
			.sh_flags = -1,
			.sh_flags_not = SHF_WRITE,
			.sh_name = "",
			.letter = 'R',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_PROGBITS,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'd',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_PROGBITS,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'D',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_DYNAMIC,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'd',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_DYNAMIC,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'D',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_INIT_ARRAY,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'd',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_INIT_ARRAY,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'D',
		},
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_FINI_ARRAY,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'd',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_FINI_ARRAY,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'D',
		}, // ASAN hack
		// 	{
		//     .st_bind = STB_GLOBAL,
		//     .st_type = -1,
		//     .st_value = -1,
		//     .st_shndx = -1,
		//     .sh_type = SHT_PROGBITS,
		//     .sh_flags = SHF_ALLOC | SHF_WRITE,
		//     .sh_flags_not = -1,
		//     .sh_name = "",
		//     .letter = 'D',
		// },
		// Para .preinit_array
		{
			.st_bind = STB_LOCAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_PREINIT_ARRAY, // Tipo específico para preinit_array
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'd',
		},
		{
			.st_bind = STB_GLOBAL,
			.st_type = -1,
			.st_value = -1,
			.st_shndx = -1,
			.sh_type = SHT_PREINIT_ARRAY,
			.sh_flags = -1,
			.sh_flags_not = -1,
			.sh_name = "",
			.letter = 'D',
		},
		{},
};

// char get_sym_type(struct s_symbol *sym)
// {

// 	struct s_sym_type_ref ref;

// 	for (size_t i = 0; symbol_type_ref[i].letter != 0; ++i)
// 	{
// 		ref = symbol_type_ref[i];
// 		if ((ref.st_bind == -1 || ref.st_bind == sym->st_bind) &&
// 			(ref.st_type == -1 || ref.st_type == sym->st_type) &&
// 			(ref.st_value == -1 || ref.st_value == sym->st_value) &&
// 			(ref.st_shndx == -1 || ref.st_shndx == sym->st_shndx) &&
// 			(ref.sh_type == -1 || ref.sh_type == sym->sh_type) &&
// 			(ref.sh_flags == -1 ||
// 			 (sym->sh_flags & ref.sh_flags) != 0) &&
// 			(ref.sh_flags_not == -1 ||
// 			 (sym->sh_flags & ref.sh_flags_not) == 0) &&
// 			(ft_strlen(ref.sh_name) == 0 ||
// 			 ft_strcmp(ref.sh_name, sym->sh_name) == 0))
// 			return ref.letter;
// 	}

// 	//printf("(%s) %d %d\n", sym->sh_name, sym->st_type, sym->st_shndx);

// 	return '?';
// }

/*
 * Determines the symbol type character for a given symbol.
 * 
 * This function iterates through a predefined set of symbol type references,
 * comparing each reference's attributes against those of the provided symbol.
 * If a reference matches the symbol's attributes, the corresponding type
 * character ('letter') is returned. If no references match, the function
 * returns '?'.
 * 
 * Parameters:
 *   sym - Pointer to the symbol structure to be evaluated.
 * 
 * Returns:
 *   The character representing the symbol type, or '?' if no match is found.
 */
char get_sym_type(struct s_symbol *sym)
{
	struct s_sym_type_ref ref;

	for (size_t i = 0; symbol_type_ref[i].letter != 0; ++i)
	{
		ref = symbol_type_ref[i];

		// Conjunto de verificações:
		// 1. Se bind é -1 (qualquer) ou igual ao do símbolo
		if ((ref.st_bind == -1 || ref.st_bind == sym->st_bind) &&
			// 2. Se tipo é -1 (qualquer) ou igual ao do símbolo
			(ref.st_type == -1 || ref.st_type == sym->st_type) &&
			// 3. Se valor é -1 (qualquer) ou igual ao do símbolo
			(ref.st_value == -1 || ref.st_value == sym->st_value) &&
			// 4. Se índice da seção é -1 (qualquer) ou igual
			(ref.st_shndx == -1 || ref.st_shndx == sym->st_shndx) &&
			// 5. Se tipo de seção é -1 (qualquer) ou igual
			(ref.sh_type == -1 || ref.sh_type == sym->sh_type) &&
			// 6. Se flags são -1 (qualquer) ou tem interseção
			(ref.sh_flags == -1 || (sym->sh_flags & ref.sh_flags) != 0) &&
			// 7. Se flags_not são -1 (qualquer) ou não tem interseção
			(ref.sh_flags_not == -1 || (sym->sh_flags & ref.sh_flags_not) == 0) &&
			// 8. Se nome da seção está vazio ou é igual
			(ft_strlen(ref.sh_name) == 0 || ft_strcmp(ref.sh_name, sym->sh_name) == 0))

			return ref.letter; 
	}

	// Se nenhuma regra corresponder, retorna '?'
	return '?';
}