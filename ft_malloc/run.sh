#!/bin/sh
#ps aux | grep ls
MALLOC_DEBUG=1 env LD_PRELOAD=./libft_malloc.so  vim test.c
