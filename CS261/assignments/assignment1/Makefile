CC = gcc --std=c99 -g
exe_file = list-array.out

$(exe_file): dynarray.o list.o driver.o
	$(CC) dynarray.o list.o driver.o -o $(exe_file)

dynarray.o: dynarray.c
	$(CC) -c dynarray.c

list.o: list.c
	$(CC) -c list.c

driver.o: driver.c
	$(CC) -c driver.c

clean:
	rm -rf *.o $(exe_file)