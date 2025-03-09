#ifndef UTILS_H
#define UTILS_H

#include <sys/stat.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>


typedef struct s_options
{
    int l; // Formato longo lista detalhada
    int R; // Recursivo
    int a; // Mostrar ficheiros ocultos
    int r; // Ordem reversa
    int t; // Ordenar por tempo de modificação
} t_options;


typedef struct s_file_info
{
    char *name;     
    char *path;      // Caminho completo
    struct stat stats; // Estatísticas do arquivo
} t_file_info;


typedef struct s_vector
{
    size_t size;              // Número de elementos
    size_t capacity;          // Capacidade total
    t_file_info **data;       // Array de ponteiros para file_info
} t_vector;


size_t      ft_strlen(const char *s);
char        *ft_strcpy(char *dest, const char *src);
char        *ft_strdup(const char *s);
int         ft_strcmp(const char *s1, const char *s2);
char        *ft_strcat(char *dest, const char *src);
void        ft_itoa(long long n, char *buffer);
void        ft_print_str(const char *str);
void        ft_join_path(char *buffer, size_t size, const char *path, const char *name);
void        ft_error_str(const char *str, const char *err, int nl);
char        *ft_strnew(size_t size);
char        *ft_strjoin(const char *s1, const char *s2);
char        *ft_strsub(const char *s, unsigned int start, size_t len);
char        *ft_strncpy(char *dst, const char *src, size_t len);


t_file_info *create_file_info(const char *name, const char *path);
void        free_file_info(t_file_info *file_info);


int         vector_init(t_vector *vector, size_t capacity);
void        vector_free(t_vector *vector);
int         vector_push(t_vector *vector, t_file_info *file_info);
void        vector_sort(t_vector *vector, t_options *opts);

void        print_simple_list(t_vector *vector,t_options *opts);
void        print_detailed_list(t_vector *vector,t_options *opts);

void        print_directory_name(const char *dir_name);
void        print_file_permissions(mode_t mode);
char        *format_time(time_t mtime);


int         compare_files(const t_file_info *a, const t_file_info *b, t_options *opts);


int         read_directory(const char *path, t_vector *vector, t_options *opts);
void        process_directory(const char *path, t_options *opts, int is_recursive, int show_dirname);

#endif
