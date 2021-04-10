CC = g++ -std=c++11 -g
exe_file = Book_Sort.out

$(exe_file): Book_Sort.o Book_Sort_Driver.o
	$(CC) Book_Sort.o Book_Sort_Driver.o -o $(exe_file)

Student_DB.o: Book_Sort.cpp
	$(CC) -c Book_Sort.cpp

DB_Driver.o: Book_Sort_Driver.cpp
	$(CC) -c Book_Sort_Driver.cpp

clean:
	rm -rf *.o $(exe_file)