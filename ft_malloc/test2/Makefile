
TEST_PROGRAM = teste

CC = gcc
CFLAGS =   -I../include 


TEST_SRC = teste.c


LDFLAGS = $(LIB)


$(TEST_PROGRAM): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC)   $(LDFLAGS) -o $(TEST_PROGRAM)


run: $(TEST_PROGRAM) 
	MALLOC_DEBUG=1  env LD_PRELOAD=../libft_malloc.so  ./$(TEST_PROGRAM)
	


val:
	 valgrind --leak-check=full  ./$(TEST_PROGRAM)


clean:
	rm -f $(TEST_PROGRAM)



.PHONY: clean run

