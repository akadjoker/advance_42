#include "nm.h"
#include <sys/mman.h> // munmap()
#include <limits.h>


#define MAX_FILE_SIZE ((size_t)LONG_MAX)



 bool is_special_file(char *filename)
{
    struct stat st;
    
    if (lstat(filename, &st) != 0)
        return false;

    return (S_ISBLK(st.st_mode) || 
            S_ISCHR(st.st_mode) || 
            S_ISFIFO(st.st_mode) ||
            S_ISSOCK(st.st_mode));
}

 bool is_valid_file_size(const t_file *file, char *filename)
{
    if ((size_t)file->infos.st_size < sizeof(Elf64_Ehdr))
    {
        PRINT_ERROR_WRONG_FILE_FORMAT(filename);
        return false;
    }
    if ((size_t)file->infos.st_size > MAX_FILE_SIZE)
    {
        PRINT_ERROR_FILE_TOO_BIG(filename);
        return false;
    }
    return true;
}

 bool is_valid_elf(const void *file, size_t size)
{
    const unsigned char *e_ident = file;

    if (size < EI_NIDENT)
        return false;
    
    return (e_ident[EI_MAG0] == ELFMAG0 &&
            e_ident[EI_MAG1] == ELFMAG1 &&
            e_ident[EI_MAG2] == ELFMAG2 &&
            e_ident[EI_MAG3] == ELFMAG3);
}


int process_file(char *filename, t_file *file, t_options *options)
{

    if (!filename || !file->file)
        return EXIT_FAILURE;


    if (is_special_file(filename))
    {
        PRINT_ERROR_SPECIAL_FILE(filename);
        return EXIT_FAILURE;
    }

     if (!is_valid_file_size(file, filename))
        return EXIT_FAILURE;

     if (!is_valid_elf(file->file, (size_t)file->infos.st_size))
    {
        PRINT_ERROR_WRONG_FILE_FORMAT(filename);
        return EXIT_FAILURE;
    }


    int result =EXIT_FAILURE;
    short arch = file->file[EI_CLASS];

    switch (arch)
    {

    case ELFCLASS32:
        if (interpret_symbol_table_x32(file, options))
            result = EXIT_SUCCESS;
        break;
    case ELFCLASS64:
        if (interpret_symbol_table_x64(file, options))
            result = EXIT_SUCCESS;
        break;
    default:
        PRINT_ERROR_WRONG_FILE_FORMAT(filename);
        break;
    }

    munmap(file->file, file->infos.st_size);
    close(file->fd);
    return result;
}

int main(int argc, char **argv)
{

    int file_count;
    t_file file;

    t_options options;
    ft_memset(&options, 0, sizeof(t_options));

    if (argc == 1)
    {
        ft_memset(&file, 0, sizeof(t_file));
        if (!open_and_map_file("a.out", &file))
            return 1;
        if (!process_file("a.out", &file, &options))
            return 1;
        return 1;
    }

    file_count = argc - 1;
    for (int i = 1; i < argc; i++)
    {
        ft_memset(&file, 0, sizeof(t_file));
        if (!open_and_map_file(argv[i], &file))
            continue;

        if (file_count > 1)
            PRINT_FILENAME(argv[i]);

        if (!process_file(argv[i], &file, &options)) 
            return 1;
    }
    return 0;
}

// int main(int argc, char **argv)
// {
//     (void)argc;
//     (void)argv;
//     t_file file;
//     t_options options;
//     //int file_nb;

//     ft_memset(&options,0,sizeof(t_options));

//     process_file(argv[1], &file,&options,1);

//     // file_nb = parse_options(&options, argv);

//     // if (file_nb == NO_FILE_ARG)
//     // {
//     //     process_file("a.out", &file, &options, file_nb);
//     //     return END;
//     // }

//     // for (int i = 1; i < argc; i++)
//     // {
//     //     process_file(argv[i], &file, &options, file_nb);
//     // }
//     return END;
// }
