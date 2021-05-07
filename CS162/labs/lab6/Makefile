CC = g++ -std=c++11 -Wall -g
exe_file = Application.out

$(exe_file): shape.o rectangle.o circle.o application.o
	$(CC) shape.o rectangle.o circle.o application.o -o $(exe_file)

shape.o: shape.cpp
	$(CC) -c shape.cpp

rectangle.o: rectangle.cpp
	$(CC) -c rectangle.cpp

circle.o: circle.cpp
	$(CC) -c circle.cpp

application.o: application.cpp
	$(CC) -c application.cpp

clean:
	rm -rf *.o $(exe_file)