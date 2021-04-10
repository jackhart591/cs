CC = g++ -std=c++11 -g
exe_file = Student_DB_Sorter

$(exe_file): Student_DB.o DB_Driver.o
	$(CC) Student_DB.o DB_Driver.o -o $(exe_file)

Student_DB.o: Student_DB.cpp
	$(CC) -c Student_DB.cpp

DB_Driver.o: DB_Driver.cpp
	$(CC) -c DB_Driver.cpp

clean:
	rm -rf *.o $(exe_file)