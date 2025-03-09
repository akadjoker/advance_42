#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

void print_directory_name(const char *dir_name)
{
    ft_print_str(dir_name);
    write(1, ":\n", 2);
}

void ft_print_filename(const char *str)
{
    if (!str)
        return;
        
    size_t len = ft_strlen(str);
    
    int needs_quotes = 0;
    for (size_t i = 0; i < len; i++)
    {
        // Caracteres que precisam de aspas: espaço, tab, newline, &, *, ?, etc.
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || 
            str[i] == '&' || str[i] == '*' || str[i] == '?' ||
            str[i] == '(' || str[i] == ')' || str[i] == '[' || 
            str[i] == ']' || str[i] == '\'' || str[i] == '"')
        {
            needs_quotes = 1;
            break;
        }
    }
    
    if (needs_quotes)
    {
        write(1, "'", 1);
        write(1, str, len);
        write(1, "'", 1);
    }
    else
    {
        write(1, str, len);
    }
}

void print_file_permissions(mode_t mode)
{
    // Tipo de arquivo
    write(1, (S_ISDIR(mode)) ? "d" : "-", 1);
    
    // Permissões do dono
    write(1, (mode & S_IRUSR) ? "r" : "-", 1);
    write(1, (mode & S_IWUSR) ? "w" : "-", 1);
    write(1, (mode & S_IXUSR) ? "x" : "-", 1);
    
    // Permissões do grupo
    write(1, (mode & S_IRGRP) ? "r" : "-", 1);
    write(1, (mode & S_IWGRP) ? "w" : "-", 1);
    write(1, (mode & S_IXGRP) ? "x" : "-", 1);
    
    // Permissões de outros
    write(1, (mode & S_IROTH) ? "r" : "-", 1);
    write(1, (mode & S_IWOTH) ? "w" : "-", 1);
    write(1, (mode & S_IXOTH) ? "x" : "-", 1);
}

char *format_time(time_t mtime)
{
    char *time_str = ctime(&mtime) + 4; // Pula "Day "
    time_t now = time(NULL);
    char *result;
    
    // Se a modificação for mais antiga que 6 meses, mostra o ano em vez da hora
    if (now - mtime > 15768000) // ~6 meses em segundos
    {
        // Format: "Mon DD  YYYY"
        result = ft_strnew(12);
        ft_strncpy(result, time_str, 7);
        ft_strncpy(result + 7, time_str + 15, 5);
    }
    else
    {
        // Format: "Mon DD HH:MM"
        result = ft_strnew(12);
        ft_strncpy(result, time_str, 12);
    }
    
    return result;
}

 
void print_simple_list(t_vector *vector, t_options *opts)
{
    size_t start, end, increment;
    
    if (opts->r)
    {
 
        start = vector->size - 1;
        end = -1; 
        increment = -1;
    }
    else
    {
 
        start = 0;
        end = vector->size;
        increment = 1;
    }
    
    for (size_t i = start; i != end; i += increment)
    {
        ft_print_filename(vector->data[i]->name);
        write(1, "\n", 1);
    }
}

void calculate_column_widths(t_vector *vector, size_t *link_width,
                           size_t *user_width, size_t *group_width,
                           size_t *size_width)
{
    char buffer[64];
    *link_width = 0;
    *user_width = 0;
    *group_width = 0;
    *size_width = 0;
    
    for (size_t i = 0; i < vector->size; i++)
    {
        t_file_info *file = vector->data[i];
        struct passwd *pw = getpwuid(file->stats.st_uid);
        struct group *gr = getgrgid(file->stats.st_gid);
        
        // Links
        ft_itoa(file->stats.st_nlink, buffer);
        size_t len = ft_strlen(buffer);
        if (len > *link_width)
            *link_width = len;
            
        // User
        if (pw) {
            len = ft_strlen(pw->pw_name);
            if (len > *user_width)
                *user_width = len;
        }
        
        // Group
        if (gr) {
            len = ft_strlen(gr->gr_name);
            if (len > *group_width)
                *group_width = len;
        }
        
        // Size
        ft_itoa(file->stats.st_size, buffer);
        len = ft_strlen(buffer);
        if (len > *size_width)
            *size_width = len;
    }
}

void print_total_blocks(t_vector *vector)
{
    long total = 0;
    char buffer[64];
    
    for (size_t i = 0; i < vector->size; i++)
        total += vector->data[i]->stats.st_blocks;
    
    // Dividir por 2 porque st_blocks usa blocos de 512 bytes
    total /= 2;
    
    ft_print_str("total ");
    ft_itoa(total, buffer);
    ft_print_str(buffer);
    write(1, "\n", 1);
}

void print_detailed_list(t_vector *vector, t_options *opts)
{
    char buffer[64];
    size_t link_width, user_width, group_width, size_width;
    
    calculate_column_widths(vector, &link_width, &user_width, &group_width, &size_width);
    print_total_blocks(vector);
    
    // Determinar a direção da iteração com base na opção -r
    size_t start, end, step;
    if (opts->r)
    {
        // Ordem reversa: do último para o primeiro
        start = vector->size - 1;
        end = (size_t)-1; // Wraparound para valor máximo de size_t
        step = -1;
    }
    else
    {
        // Ordem normal: do primeiro para o último
        start = 0;
        end = vector->size;
        step = 1;
    }
    
    // Iterar pelo vetor na direção correta
    for (size_t i = start; i != end; i = (i + step))
    {
        t_file_info *file = vector->data[i];
        struct passwd *pw = getpwuid(file->stats.st_uid);
        struct group *gr = getgrgid(file->stats.st_gid);
        
        // Permissões
        print_file_permissions(file->stats.st_mode);
        write(1, " ", 1);
        
        // Número de links
        ft_itoa(file->stats.st_nlink, buffer);
        size_t padding = link_width - ft_strlen(buffer);
        while (padding--)
            write(1, " ", 1);
        ft_print_str(buffer);
        write(1, " ", 1);
        
        // Usuário
        if (pw)
        {
            ft_print_str(pw->pw_name);
            padding = user_width - ft_strlen(pw->pw_name);
            while (padding--)
                write(1, " ", 1);
            write(1, "  ", 2);
        }
        
        // Grupo
        if (gr)
        {
            ft_print_str(gr->gr_name);
            padding = group_width - ft_strlen(gr->gr_name);
            while (padding--)
                write(1, " ", 1);
            write(1, "  ", 2);
        }
        
        // Tamanho
        ft_itoa(file->stats.st_size, buffer);
        padding = size_width - ft_strlen(buffer);
        while (padding--)
            write(1, " ", 1);
        ft_print_str(buffer);
        write(1, " ", 1);
        
        // Data
        char *time_str = format_time(file->stats.st_mtime);
        ft_print_str(time_str);
        free(time_str);
        write(1, " ", 1);
        
        // Nome
        ft_print_filename(file->name);
        
        // Link simbólico
        if (S_ISLNK(file->stats.st_mode))
        {
            char link_target[4096];
            ssize_t len = readlink(file->path, link_target, sizeof(link_target) - 1);
            if (len != -1)
            {
                link_target[len] = '\0';
                ft_print_str(" -> ");
                ft_print_filename(link_target);
            }
        }
        
        write(1, "\n", 1);
    }
}

