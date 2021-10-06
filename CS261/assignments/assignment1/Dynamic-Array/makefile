CC = gcc --std=c99 -g
exe_file = dynarray.out

$(exe_file): dynarray.o
	$(CC) dynarray -o $(exe_file)

dynarray.o: dynarray.c
	$(CC) -c dynarray.c

clean:
	rm -rf *.o $(exe_file)