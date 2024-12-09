#ifndef FT_MALLOC_INTERNAL_H
#define FT_MALLOC_INTERNAL_H

#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdint.h>


#include <stddef.h>
#include <unistd.h> // write()
#include <stdbool.h>  // bool type



#define EXPORT __attribute__((visibility("default")))

#define MALLOC_DEBUG 0
#define SINGLE_THREAD 0

#define MAX_SIZE_TINY 512
#define MAX_SIZE_SMALL 4096

#define ALIGN (2 * sizeof(size_t))

/*

 Make sure alignment is power of 2.  malloc on lib.c
  if (!powerof2 (alignment))
    {
      size_t a = MALLOC_ALIGNMENT * 2;
      while (a < alignment)
        a <<= 1;
      alignment = a;
    }

*/


typedef enum e_type_zone
{
    unused = 0,
    tiny,
    small,
    large
} t_type_zone;

typedef struct s_block
{
    size_t size;
    unsigned int indexZone;
    char free;
} t_block;

typedef struct s_zone
{
    t_type_zone type;
    size_t size; // size alloc - sizeof(t_zone)
} t_zone;

typedef struct s_zones
{
    size_t pageAlloc;
    size_t size;
    size_t numPage;
    size_t pageSize;
    size_t maxPage;
    bool debug;
    bool init;
    t_zone **zones;
} t_zones;

extern t_zones g_zone;


void set_block(t_block *block, size_t size);
t_block *find_freeblock(size_t size, t_type_zone typeZone);

// freeZone
void ft_unmap(void *ptr, size_t size);//secure unmap
int   check_block(void *data);
void freeZone();
void remove_block(t_block *zone);

bool isDebug();

// debug
void puthex(unsigned long long int hex, int min);
void debug_str(char *str);
void debug_var(char *name, long long int var, char *end);
void debug_hex(char *name, void *var, char *end);

// zone
//ver allockzone para a * por 100 como subject
void free_all_zones(void);
t_block *getNextBlock(t_block *block);
t_block *getFirstBlock(void *zone);
void initZone(t_zone *zone, t_type_zone typeZone, size_t size);
void initBlock(void *zone, size_t size, unsigned int indexZone);
int isLastBlock(t_block *block);
t_block *getPrevBlock(t_block *block);
int getSizeZone(size_t size);

//internal
void *ft_malloc(size_t size);
void ft_free(void *ptr);
void *ft_realloc(void *ptr, size_t size);
void *ft_calloc(size_t nmemb, size_t size);
void ft_lock();
void ft_unlock();


//utils
void ft_putstr(char const *s);
int ft_putchar(int c);
void ft_putaddr(void *ptr);
size_t ft_strlen(const char *str);
void *ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void		ft_itoa_base(long long int value, int base);
int	   ft_strcmp(const char *s1, const char *s2);

void ft_putnbr_base(size_t nbr, char *base, int base_len);
void		ft_putnbr(int n);

#endif