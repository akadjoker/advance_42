gcc test.c -o test
MALLOC_DEBUG=1 env LD_PRELOAD=./libft_malloc.so ./test
