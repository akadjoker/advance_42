
#include <signal.h>
#include "internal.h"
#include "ft_malloc.h"

/**
 * Initializes a memory zone with specified type and size.
 *
 * @param zone Pointer to the memory zone to be initialized.
 * @param typeZone The type of the memory zone (tiny, small, or large).
 * @param size The size of the memory zone, excluding the size of the zone metadata.
 */
void initZone(t_zone *zone, t_type_zone typeZone, size_t size)
{
    zone->type = typeZone;
    zone->size = size;
}

/**
 * Initializes a memory block within a zone.
 *
 * @param zone Pointer to the memory block to be initialized.
 * @param size The size of the memory block.
 * @param indexZone The index of the zone where the block is located.
 */
void initBlock(void *zone, size_t size, unsigned int indexZone)
{
    t_block *block;

    block = zone;
    block->size = size;
    block->free = 1;
    block->indexZone = indexZone;
}

/**
 * Retrieves the first block within a given memory zone.
 *
 * @param zone Pointer to the memory zone.
 * @return Pointer to the first block in the specified zone.
 */
t_block *getFirstBlock(void *zone)
{
    return zone + sizeof(t_zone);
}

/**
 * Retrieves the next memory block following the given block.
 *
 * @param block Pointer to the current memory block.
 * @return Pointer to the next memory block.
 */
t_block *getNextBlock(t_block *block)
{
    return ((void *)block + sizeof(t_block) + block->size);
}

/**
 * Retrieves the previous memory block before the given block within a zone.
 *
 * @param block Pointer to the current memory block.
 * @return Pointer to the previous memory block, or NULL if the
 *         given block is the first block in the zone.
 */
t_block *getPrevBlock(t_block *block)
{
    t_block *prev;
    t_block *next;

    next = NULL;
    prev = getFirstBlock(g_zone.zones[block->indexZone]);
    while (block != prev)
    {
        next = getNextBlock(prev);
        if (next == block)
            return (prev);
        prev = next;
    }
    return (NULL);
}

/**
 * Checks whether the given block is the last block in its zone.
 *
 * @param block Pointer to the memory block to be checked.
 * @return 1 if the block is the last block in the zone, 0 otherwise.
 */
int isLastBlock(t_block *block)
{
    t_zone *zone;

    zone = g_zone.zones[block->indexZone];
    if ((void *)getFirstBlock(zone) + zone->size == getNextBlock(block))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * Determines the appropriate zone type for a given block size.
 *
 * @param size The size of the memory block.
 * @return The type of the memory zone (tiny, small, or large) based on the block size.
 */
int getSizeZone(size_t size)
{
    if (size <= MAX_SIZE_TINY)
    {
        return (tiny);
    }
    else if (size <= MAX_SIZE_SMALL)
    {
        return (small);
    }
    else
    {
        return (large);
    }
}

void ft_unmap(void *ptr, size_t size)
{

    g_zone.pageAlloc -= size / g_zone.pageSize;
    munmap(ptr, size);
}

/**
 * Checks if a given pointer is within the bounds of any allocated block.
 *
 * @param data The pointer to be checked.
 * @return 1 if the pointer is within the bounds of an allocated block, 0 otherwise.
 *
 * This function iterates over all zones and checks if the given pointer is within
 * the bounds of any block within a zone. If the pointer is within the bounds of
 * an allocated block, it returns 1; otherwise, it returns 0.
 */
int check_block(void *data)
{
    t_zone *zone;
    t_block *block;
    size_t size;

    for (unsigned int index = 0; index < g_zone.size; index++)
    {
        zone = g_zone.zones[index];
        if (zone && (void *)zone + sizeof(t_zone) < (void *)data && (void *)data < (void *)zone + sizeof(t_zone) + zone->size)
        {
            block = (void *)zone + sizeof(t_zone);
            size = zone->size;
            while (size)
            {
                if ((void *)block + sizeof(t_block) == data)
                    return 1;
                size -= sizeof(t_block) + block->size;
                block = getNextBlock(block);
            }
        }
    }
    return 0;
}

/**
 * Frees unused memory zones by unmapping them with ft_unmap.
 *
 * This function is called by ft_free to free unused memory zones.
 * It iterates over all zones and checks if the first block of each zone
 * is free and has a size equal to the zone size. If the zone is unused and
 * its first block is free, it unmaps the zone with ft_unmap and sets
 * the corresponding element in g_zone.zones to NULL.
 */
void freeZone()
{
    int counterTypeZone[4];
    t_zone *zone;

    counterTypeZone[0] = 0; // unusable
    counterTypeZone[1] = 0; // tiny
    counterTypeZone[2] = 0; // small
    counterTypeZone[3] = 0; // large
    for (unsigned int index = 0; index < g_zone.size; index++)
    {
        zone = g_zone.zones[index];
        if (zone)
        {
            counterTypeZone[zone->type]++;
            if (counterTypeZone[zone->type] > 1 && getFirstBlock(zone)->free && getFirstBlock(zone)->size + sizeof(t_block) == zone->size)
            {
                debug_var("[*] freeZone( ", zone->size, " )\n");
                ft_unmap(zone, zone->size + sizeof(t_zone));
                g_zone.zones[index] = NULL;
            }
        }
    }
}

void free_all_zones(void)
{
    ft_lock();
    if (g_zone.size==0) return ;
    for (unsigned int index = 0; index < g_zone.size - 1; index++)
    {
        t_zone *zone = g_zone.zones[index];
        if (zone)
        {
            debug_var("[*] Free zon (", zone->size, " bytes)\n");
            ft_unmap(zone, zone->size + sizeof(t_zone));
            // g_zone.zones[index] = NULL; // Remove a referência no array
        }
    }

    ft_unlock();
    g_zone.size=0;
   

    debug_str("[*] free_all_zones()\n");
}

/**
 * Marks a memory block as free and merges adjacent free blocks.
 *
 * This function is called by ft_free to mark a memory block as free.
 * It checks if the block is the last block in the zone and if the next
 * block is free, and if so, it merges the blocks by adding the size of
 * the next block to the current block and zeroing out the next block.
 * It also checks if the previous block is free and if so, it merges the
 * blocks in a similar way.
 */
void remove_block(t_block *block)
{
    t_block *next;
    t_block *prev;

    block->free = 1;
    debug_var("[*] remove_block( ", block->size, " )\n");
    if (!isLastBlock(block))
    {
        next = getNextBlock(block);
        if (next->free)
        {
            block->size += sizeof(t_block) + next->size;
            ft_bzero(next, sizeof(t_block));
        }
    }
    if ((prev = getPrevBlock(block)))
    {
        if (prev->free)
        {
            prev->size += sizeof(t_block) + block->size;
            ft_bzero(block, sizeof(t_block));
        }
    }
}

/**
 * Initializes a memory block and splits it into two blocks if there is enough space.
 *
 * This function is called by ft_malloc and ft_realloc to mark a memory block as allocated.
 * It checks if the block has enough space to be split into two blocks, and if so, it
 * initializes the second block as free and sets the size of the first block to the
 * requested size.
 */
void set_block(t_block *block, size_t size)
{
    block->free = 0;
    if (block->size - size >= sizeof(t_block))
    {
        initBlock(
            (void *)block + sizeof(t_block) + size,
            block->size - size - sizeof(t_block),
            block->indexZone);
        block->size = size;
    }
}

/**
 * Securely maps a given memory range.
 *
 * @param size The size of the memory range to be mapped.
 *
 * This function is used to map memory ranges allocated with ft_malloc.
 * It is "secure" because it first checks if the total number of pages allocated
 * does not exceed the maximum number of pages allowed, and then calls mmap to
 * map the memory range. If the limit is exceeded, it returns NULL.
 */
static void *ft_map(size_t size)
{
    int nbPage = size / g_zone.pageSize;

    if (g_zone.maxPage < g_zone.pageAlloc + nbPage)
    {
        debug_var("Limit of memory, can't mmap. ( maxPage=", g_zone.maxPage, "");
        debug_var(", pageAlloc=", g_zone.pageAlloc, " )");
        return (NULL);
    }
    g_zone.pageAlloc += nbPage;
    return mmap(NULL,
                size,
                PROT_READ | PROT_WRITE,
                MAP_ANONYMOUS | MAP_PRIVATE,
                -1,
                0);
}

/**
 * Allocates a new memory zone with specified type and size.
 *
 * @param sizeBlock The size of the blocks within the zone.
 * @param typeZone The type of the memory zone (tiny, small, or large).
 *
 * This function allocates a new memory zone with the specified type and size,
 * and initializes the zone with the given size and type. If the type is tiny
 * or small, it allocates a zone with the maximum size for that type; otherwise,
 * it allocates a zone with the given size. It also initializes the first block
 * of the zone with the given size and type. Finally, it returns a pointer to the
 * newly allocated zone.
 *
 * If the allocation fails, it returns NULL.
 */
static void *allocZone(size_t sizeBlock, t_type_zone typeZone)
{
    t_zone *zone;
    size_t real_size;

    if (typeZone == tiny)
    {
        sizeBlock = MAX_SIZE_TINY;
    }
    else if (typeZone == small)
    {
        sizeBlock = MAX_SIZE_SMALL;
    }
    real_size = (sizeBlock + sizeof(t_block));
    if (typeZone != large)
    {
        //Para zonas tiny e small: multiplica por 100 para criar múltiplos blocos
        real_size *= 100;
    }
    //Para zonas large: mantém o tamanho original

    //Adiciona o tamanho do header da zona
    real_size += sizeof(t_zone);
    //Arredonda para o próximo múltiplo de pageSize, garante alinhamento com o tamanho das páginas do sistema
    real_size = ((real_size - 1) / g_zone.pageSize) * g_zone.pageSize + g_zone.pageSize;
    if ((zone = ft_map(real_size)) == (void *)-1)
    {
        return (NULL);
    }
    initZone(zone, typeZone, real_size - sizeof(t_zone));
    initBlock(getFirstBlock(zone), real_size - sizeof(t_zone) - sizeof(t_block), 0);
    return (zone);
}

/**
 * Allocates a new table of memory zones and copies the old table to the new one.
 *
 * This function is called by addZone when the table of memory zones is full.
 * It allocates a new table with one more page than the old one, copies the
 * old table to the new one, and sets up the new table as the current table
 * of memory zones. If the allocation fails, it returns without doing anything.
 */
static void allocTabZones()
{
    t_zone **newZones;

    if ((newZones = ft_map((g_zone.numPage + 1) * g_zone.pageSize)) == (void *)-1)
        return;
    if (g_zone.zones)
    {
        ft_memcpy(newZones, g_zone.zones, g_zone.numPage * g_zone.pageSize);
        ft_unmap(g_zone.zones, g_zone.numPage * g_zone.pageSize);
    }
    g_zone.numPage++;
    g_zone.size = (g_zone.numPage * g_zone.pageSize) / sizeof(t_zone *);
    g_zone.zones = newZones;
}

/**
 * Adds a given memory zone to the table of memory zones.
 *
 * @param zone The memory zone to be added to the table.
 * @return 1 if the zone was successfully added, 0 otherwise.
 *
 * This function iterates over the table of memory zones and adds the given
 * zone to the first empty slot it finds. If the zone is successfully added,
 * it also sets the indexZone field of the first block in the zone to the
 * index of the slot in the table. If the table is full, it returns 0.
 */
static int addZoneToTab(t_zone *zone)
{
    t_block *block;

    for (unsigned int index = 0; index < g_zone.size; index++)
    {
        if (!g_zone.zones[index])
        {
            g_zone.zones[index] = zone;
            block = getFirstBlock(zone);
            block->indexZone = index;
            return 1;
        }
    }
    return 0;
}

/**
 * Adds a new memory zone of the specified size and type.
 *
 * This function attempts to allocate and add a new memory zone to the
 * existing table of memory zones. If the allocation is successful but
 * the table is full, it reallocates a larger table and retries adding
 * the zone.
 *
 * @param size The size of the zone to allocate.
 * @param typeZone The type of the zone (tiny, small, or large).
 */
static void addZone(size_t size, t_type_zone typeZone)
{
    t_zone *new;

    if (!(new = allocZone(size, typeZone)))
        return;
    if (!addZoneToTab(new))
    {
        allocTabZones();
        addZoneToTab(new);
    }
}

/**
 * Recursively searches for a free block of memory within a zone that
 * can accommodate the requested size.
 *
 * @param block Pointer to the current memory block being inspected.
 * @param size The size of the memory block required.
 * @param sizeZone The remaining size of the zone to be searched.
 * @return Pointer to a suitable free block if found, NULL otherwise.
 */
static t_block *findFreeBlock(t_block *block, size_t size, size_t sizeZone)
{
    if (sizeZone <= 0)
    {
        return (NULL);
    }
    if (block->free && block->size >= size)
    {
        return (block);
    }
    return findFreeBlock(getNextBlock(block), size, sizeZone - sizeof(t_block) - block->size);
}

/**
 * Searches all memory zones of a given type for a free memory block that can accommodate
 * the specified size.
 *
 * @param size The size of the memory block required.
 * @param typeZone The type of the memory zone to be searched.
 * @return Pointer to the first free block of memory that can accommodate the size, or NULL
 *         if none is found.
 */
static void *findBlock(size_t size, t_type_zone typeZone)
{
    t_block *block;

    for (unsigned int index = 0; index < g_zone.size; index++)
    {
        if (g_zone.zones[index] && g_zone.zones[index]->type == typeZone)
        {
            block = findFreeBlock(getFirstBlock(g_zone.zones[index]), size, g_zone.zones[index]->size);
            if (block)
            {
                return block;
            }
        }
    }
    return (NULL);
}

/**
 * Searches all memory zones of a given type for a free memory block that can accommodate
 * the specified size. If a free block is not found, it allocates a new zone of the specified
 * type and size, and then searches again for a free block.
 *
 * @param size The size of the memory block required.
 * @param typeZone The type of the memory zone to be searched.
 * @return Pointer to the first free block of memory that can accommodate the size, or NULL
 *         if the allocation fails.
 */
t_block *find_freeblock(size_t size, t_type_zone typeZone)
{
    void *free_block;

    if (!g_zone.zones)
    {
        allocTabZones();
    }
    free_block = findBlock(size, typeZone);
    if (free_block)
    {
        return free_block;
    }
    else
    {
        addZone(size, typeZone);
        return findBlock(size, typeZone);
    }
}

bool isDebug()
{

    if (!g_zone.init)
    {
        char *env;
        env = getenv("MALLOC_DEBUG");
        if (ft_strcmp(env, "0") == 0)
        {
            g_zone.debug = false;
        }
        else if (ft_strcmp(env, "1") == 0)
        {
            g_zone.debug = true;
        }
    }
    return g_zone.debug;
}

// IMPLEMENT
//************************************************************************************** */

pthread_mutex_t g_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
t_zones g_zone = {0, 0, 0, 0, 0, 0, 0, 0};

void ft_lock()
{
#if !defined(SINGEL_THREAD)
    pthread_mutex_lock(&g_mutex);
#endif
}

void ft_unlock()
{
#if !defined(SINGEL_THREAD)
    pthread_mutex_unlock(&g_mutex);
#endif
}

/**
 * Allocates a block of memory of the specified size.
 *
 * This function attempts to allocate a block of memory with the given size,
 * aligning it to the nearest multiple of the defined alignment value. If the
 * allocation is successful, it returns a pointer to the newly allocated block,
 * otherwise, it returns NULL. The function also initializes global zone
 * parameters such as page size and maximum page limit if they haven't been
 * set yet.
 *
 * @param size The size of the memory block to be allocated.
 * pageSize = getpagesize() * 100;
 * @return Pointer to the allocated memory block, or NULL if the allocation fails.
 */
void *ft_malloc(size_t size)
{
    void *block;
    struct rlimit rlim;

    if (!size)
    {
        return (NULL);
    }
    if (!g_zone.pageSize)
        g_zone.pageSize = getpagesize(); // on ini set page size * 100 like subject say so
    if (!g_zone.maxPage)
    {
        if (getrlimit(RLIMIT_DATA, &rlim) < 0)
            return (NULL);
        g_zone.maxPage = rlim.rlim_cur / g_zone.pageSize;
    }
    size = ((size - 1) / ALIGN) * ALIGN + ALIGN;
    if (!(block = find_freeblock(size, getSizeZone(size))))
    {
        return (NULL);
    }
    set_block(block, size);
    return (block + sizeof(t_block));
}

/**
 * Frees the memory block pointed to by ptr.
 *
 * This function frees the memory block pointed to by ptr, and if the block is
 * the last block in the zone, it unmaps the zone with ft_unmap and sets the
 * corresponding element in g_zone.zones to NULL.
 *
 * @param ptr Pointer to the memory block to be freed.
 */
void ft_free(void *ptr)
{
    if (!ptr)
        return;
    if (!check_block(ptr))
        return;
    remove_block(ptr - sizeof(t_block));
    freeZone();
}

/**
 * Reallocates a memory block to a new size.
 *
 * This function attempts to resize the memory block pointed to by ptr to the specified size.
 * If ptr is NULL, it behaves like ft_malloc and allocates a new block of the given size.
 * If size is 0, it behaves like ft_free and deallocates the block pointed to by ptr.
 * If the block's current size is less than the requested size, a new block is allocated,
 * the contents are copied, and the old block is freed. If the reallocation is successful,
 * a pointer to the reallocated block is returned; otherwise, NULL is returned.
 *
 * @param ptr Pointer to the memory block to be reallocated.
 * @param size The new size for the memory block.
 * @return Pointer to the reallocated memory block, or NULL if the reallocation fails.
 */
void *ft_realloc(void *ptr, size_t size)
{
    t_block *block;
    void *new;
    size_t prevSize;

    if (!ptr)
        return ft_malloc(size);
    if (!size)
    {
        ft_free(ptr);
        return (NULL);
    }

    if (!check_block(ptr))
        return (NULL);
    block = ptr - sizeof(t_block);
    size = ((size - 1) / ALIGN) * ALIGN + ALIGN;
    if (block->size < size)
    {
        prevSize = block->size;
        remove_block(block);
        if (!(new = find_freeblock(size, getSizeZone(size))))
        {
            return (NULL);
        }
        set_block(new, size);
        new += sizeof(t_block);
        if (new != ptr)
            ft_memcpy(new, ptr, prevSize);
        return (new);
    }
    else
    {
        return (ptr);
    }
}

/**
 * Allocates a block of memory of the given size, and initializes it to zero.
 *
 * @param nmemb The number of elements in the block of memory.
 * @param size The size of each element in the block of memory.
 * @return Pointer to the allocated memory block, or NULL if the allocation fails.
 */
void *ft_calloc(size_t nmemb, size_t size)
{
    if (SIZE_MAX / size < nmemb)
        return (NULL);
    size *= nmemb;
    void *ret = ft_malloc(size);
    if (ret)
        ft_bzero(ret, size);
    return ret;
}

