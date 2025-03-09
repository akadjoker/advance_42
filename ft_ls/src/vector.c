#include <sys/stat.h>
#include <string.h>
#include "utils.h"

int vector_init(t_vector *vector, size_t capacity)
{
    vector->size = 0;
    vector->capacity = capacity;
    vector->data = malloc(capacity * sizeof(t_file_info *));
    if (!vector->data)
        return 0;
    return 1;
}

static int _resize_vector(t_vector *vector, size_t new_capacity)
{
    t_file_info **new_data = malloc(new_capacity * sizeof(t_file_info *));
    if (!new_data)
        return 0;

    for (size_t i = 0; i < vector->size; i++)
        new_data[i] = vector->data[i];

    free(vector->data);
    vector->data = new_data;
    vector->capacity = new_capacity;

    return 1;
}

int vector_push(t_vector *vector, t_file_info *file_info)
{
    if (vector->size == vector->capacity)
    {
        size_t new_capacity = vector->capacity * 2;
        if (!_resize_vector(vector, new_capacity))
            return 0;
    }
    vector->data[vector->size++] = file_info;
    return 1;
}

void vector_free(t_vector *vector)
{
    if (!vector || !vector->data)
        return;
        
    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->data[i])
            free_file_info(vector->data[i]);
    }

    free(vector->data);
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

void swap_elements(t_file_info **a, t_file_info **b)
{
    t_file_info *temp = *a;
    *a = *b;
    *b = temp;
}

/*
LC_ALL=C ls
LC_ALL=C ./ft_ls
int ft_strcmp_local(const char *s1, const char *s2)
{
    setLocale(LC_COLLATE,"");
    return strcoll(s1,s2);
}
*/


int compare_files(const t_file_info *a, const t_file_info *b, t_options *opts)
{
  
    
    // Ordenar por tempo de modificação
    if (opts->t)
    {
        if (a->stats.st_mtime != b->stats.st_mtime)
        {
            return (a->stats.st_mtime > b->stats.st_mtime) ? -1 : 1;
        }
    }
    
    return  ft_strcmp(a->name, b->name);
  
}





void merge(t_file_info **data, t_file_info **temp, int left, int mid, int right, t_options *opts)
{
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right)
    {
        if (compare_files(data[i], data[j], opts) <= 0)
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while (i <= mid)
        temp[k++] = data[i++];

    while (j <= right)
        temp[k++] = data[j++];

    for (i = left; i <= right; i++)
        data[i] = temp[i];
}


void merge_sort_recursive(t_file_info **data, t_file_info **temp, int left, int right, t_options *opts)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort_recursive(data, temp, left, mid, opts);
    merge_sort_recursive(data, temp, mid + 1, right, opts);
    merge(data, temp, left, mid, right, opts);
}

void bubble_sort(t_vector *vector, t_options *opts)
{
    for (size_t i = 0; i < vector->size - 1; i++)
    {
        for (size_t j = 0; j < vector->size - i - 1; j++)
        {
            if (compare_files(vector->data[j], vector->data[j + 1], opts) > 0)
            {
 
                t_file_info *temp = vector->data[j];
                vector->data[j] = vector->data[j + 1];
                vector->data[j + 1] = temp;
            }
        }
    }
}
 

void vector_sort(t_vector *vector, t_options *opts)
{
    


    if (vector->size < 2)
        return;

    if (vector->size < 10)
    {
        bubble_sort(vector, opts);
        return;
    }

    t_file_info **temp = malloc(vector->size * sizeof(t_file_info *));
    if (!temp)
        return; 

    merge_sort_recursive(vector->data, temp, 0, vector->size - 1, opts);
    free(temp);
}

