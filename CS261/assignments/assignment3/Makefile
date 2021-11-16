CC=gcc --std=c99 -g

all: test_bst

test_bst: test_bst.c bst.o
	$(CC) test_bst.c bst.o -o test_bst

bst.o: bst.c bst.h
	$(CC) -c bst.c

clean:
	rm -f *.o test_bst