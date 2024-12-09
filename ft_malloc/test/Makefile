
TEST_PROGRAM = teste

CC = cc
CFLAGS = -Wall  -I../include -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer


TEST_SRC = teste.c


LDFLAGS = $(LIB)


$(TEST_PROGRAM): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC)   $(LDFLAGS) -o $(TEST_PROGRAM)
	MALLOC_DEBUG=0  ./$(TEST_PROGRAM)  

run: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

gdb:
	gdb --args ./$(TEST_PROGRAM)

val:
	valgrind --leak-check=full ./$(TEST_PROGRAM)

re:
	make clean
	make

clean:
	rm -f $(TEST_PROGRAM)

.PHONY: clean run

