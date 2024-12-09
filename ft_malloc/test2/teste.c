
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Buffer
{
    char a1[1024];
    long a2[1024];
    long long a3[1024];

} Buffer;


void teste_buffer()
{

    for (int i = 0; i < 100; i++)
    {
        Buffer *buffer = (Buffer *)malloc(sizeof(Buffer));
        free(buffer);
    }
}

void test_intensive_alloc(void)
{
    void *ptrs[1000];
    for (int i = 0; i < 1000; i++)
    {
        ptrs[i] = malloc(rand() % 4096); // Tamanhos aleatórios
    }
    //  em ordem aleatória
    for (int i = 999; i >= 0; i--)
    {
        free(ptrs[i]);
    }
}

void test_fragmentation(void)
{
    void *ptrs[100];
    // Aloca alternando entre pequeno e grande
    for (int i = 0; i < 100; i++)
    {
        ptrs[i] = malloc(i % 2 ? 32 : 4096);
    }
    // Liberta só os pequenos
    for (int i = 0; i < 100; i += 2)
    {
        free(ptrs[i]);
    }
    // Tenta alocar médios
    for (int i = 0; i < 50; i++)
    {
       void* p=  malloc(512);
       (void)p; //LEAK LEAK 
    }
}

void test_edge_cases(void)
{
    void* v =malloc(0);          // Tamanho zero
    v = malloc((size_t)-1); // Tamanho máximo
    (void)v;
    free(NULL);         // Free NULL
    void *ptr = malloc(16);
    free(ptr);
    free(ptr); // Double free
}

void *thread_func(void *arg)
{
    for (int i = 0; i < 1000; i++)
    {
        void *ptr = malloc(rand() % 1024);
        free(ptr);
    }
    return NULL;
}

void test_threads(void)
{
    pthread_t threads[10];
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }
}


void test_realloc(void)
{
    void *ptr = malloc(64);
    for (int i = 1; i < 100; i++)
    {
        ptr = realloc(ptr, i * 64); // up
    }
    for (int i = 100; i > 0; i--)
    {
        ptr = realloc(ptr, i * 32); // down
    }
    free(ptr);
}

void test_memory_pressure(void)
{
    void *ptrs[10000];
    size_t count = 0;

    // Aloca até não conseguir mais
    while (count < 10000)
    {
        ptrs[count] = malloc(1024 * 1024); // 1MB cada
        if (!ptrs[count])
            break;
        count++;
    }

    for (size_t i = 0; i < count; i++)
    {
        free(ptrs[i]);
    }
}

int main()
{
    printf("Starting malloc stress tests...\n");

    printf("\nTesting intensive allocations...\n");
    test_intensive_alloc();

    printf("\nTesting fragmentation...\n");
    test_fragmentation();

    printf("\nTesting edge cases...\n");
    test_edge_cases();

    printf("\nTesting multithreaded allocations...\n");
    test_threads();

    printf("\nTesting realloc...\n");
    test_realloc();

    printf("\nTesting memory pressure...\n");
    test_memory_pressure();


    printf("\nTesting memory buffers...\n");

    teste_buffer();

    printf("\nAll tests completed!\n");
    return 0;
}