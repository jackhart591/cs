CC=gcc --std=c99 -g

all: test_stack test_queue

test_stack: test_stack.c stack.o list.o
	$(CC) test_stack.c stack.o list.o -o test_stack

test_queue: test_queue.c queue.o dynarray.o
	$(CC) test_queue.c queue.o dynarray.o -o test_queue

dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c

list.o: list.c list.h
	$(CC) -c list.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

stack.o: stack.c stack.h
	$(CC) -c stack.c

clean:
	rm -f *.o test_stack test_queue