#include <sys/stat.h>
#include <stdlib.h>
#include "utils.h"

t_file_info *create_file_info(const char *name, const char *path)
{
    t_file_info *file = malloc(sizeof(t_file_info));
    if (!file)
        return NULL;
        
    file->name = ft_strdup(name);
    if (!file->name)
    {
        free(file);
        return NULL;
    }
    
    file->path = ft_strdup(path);
    if (!file->path)
    {
        free(file->name);
        free(file);
        return NULL;
    }
    
    return file;
}

void free_file_info(t_file_info *file)
{
    if (!file)
        return;
        
    free(file->name);
    free(file->path);
    file->name = NULL;
    file->path = NULL;
    free(file);
}
