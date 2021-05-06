CC = g++ -std=c++11 -Wall -g
exe_file = ZooTycoon.out

$(exe_file): Animal.o Tiger.o BlackBear.o Lemur.o Zoo.o ZooTycoon.o
	$(CC) Animal.o Tiger.o BlackBear.o Lemur.o Zoo.o ZooTycoon.o -o $(exe_file)

Animal.o: Animal.cpp
	$(CC) -c Animal.cpp

Tiger.o: Tiger.cpp
	$(CC) -c Tiger.cpp

BlackBear.o: BlackBear.cpp
	$(CC) -c BlackBear.cpp

Lemur.o: Lemur.cpp
	$(CC) -c Lemur.cpp

Zoo.o: Zoo.cpp
	$(CC) -c Zoo.cpp

ZooTycoon.o: ZooTycoon.cpp
	$(CC) -c ZooTycoon.cpp

clean:
	rm -rf *.o $(exe_file)