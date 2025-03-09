#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int read_directory(const char *path, t_vector *vector, t_options *opts)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("ft_ls");
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)))
    {
        if (!opts->a && entry->d_name[0] == '.')
            continue; // Pula arquivos ocultos se a opção -a não estiver presente

        char full_path[4096];
        ft_join_path(full_path, sizeof(full_path), path, entry->d_name);

        struct stat file_stat;
        if (lstat(full_path, &file_stat) == -1)
            continue;

        t_file_info *file_info = create_file_info(entry->d_name, full_path);
        if (!file_info)
            continue;

        file_info->stats = file_stat;
        vector_push(vector, file_info);
    }

    closedir(dir);
    return 1;
}

void process_directory(const char *path, t_options *opts, int is_recursive, int show_dirname)
{
    (void)is_recursive;
    t_vector vector;
    if (!vector_init(&vector, 100))
        return;

    if (!read_directory(path, &vector, opts))
    {
        vector_free(&vector);
        return;
    }

    vector_sort(&vector, opts);
    
    if (show_dirname)
    {
        print_directory_name(path);
    }

    if (opts->l)
        print_detailed_list(&vector,opts);
    else
        print_simple_list(&vector,opts);

    if (opts->R)
    {
        for (size_t i = 0; i < vector.size; i++)
        {
            t_file_info *file = vector.data[i];
            
            if (S_ISDIR(file->stats.st_mode) &&
                ft_strcmp(file->name, ".") != 0 &&
                ft_strcmp(file->name, "..") != 0)
            {
                write(1, "\n", 1);
                process_directory(file->path, opts, 1, 1);
            }
        }
    }

    vector_free(&vector);
}

int main(int argc, char **argv)
{
    t_options opts = {0};
    int i = 1;
    
    // Parse options
    while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
    {
        char *opt = argv[i] + 1;
        while (*opt)
        {
            if (*opt == 'l')
                opts.l = 1;
            else if (*opt == 'R')
                opts.R = 1;
            else if (*opt == 'a')
                opts.a = 1;
            else if (*opt == 'r')
                opts.r = 1;
            else if (*opt == 't')
                opts.t = 1;
            else
            {
                ft_error_str("ft_ls: illegal option -- ", opt, 1);
                return 1;
            }
            opt++;
        }
        i++;
    }

    // No args given - process current directory
    if (i == argc)
    {
        process_directory(".", &opts, 0, 0);
        return 0;
    }

    // Process each argument
    int first = 1;
    int multiple_args = (i < argc - 1);
    
    while (i < argc)
    {
        struct stat st;
        
        if (lstat(argv[i], &st) == -1)
        {
            ft_error_str("ft_ls: ", argv[i], 0);
            ft_error_str(": No such file or directory", "", 1);
            i++;
            continue;
        }
        
        if (!first)
            write(1, "\n", 1);
            
        if (S_ISDIR(st.st_mode))
        {
            process_directory(argv[i], &opts, 0, multiple_args);
        }
        else
        {
            // Single file
            t_vector vector;
            if (vector_init(&vector, 1))
            {
                t_file_info *file = create_file_info(argv[i], argv[i]);
                if (file)
                {
                    file->stats = st;
                    vector_push(&vector, file);
                    
                    if (opts.l)
                        print_detailed_list(&vector,&opts);
                    else
                        print_simple_list(&vector,&opts);
                    
                    vector_free(&vector);
                }
            }
        }
        
        first = 0;
        i++;
    }
    
    return 0;
}
