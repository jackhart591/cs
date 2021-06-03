CC = g++ -std=c++11 -Wall -g
exe_file = list.out

$(exe_file): Node.o Linked_List.o driver.o
	$(CC) Node.o Linked_List.o driver.o -o $(exe_file)

Node.o: Node.cpp
	$(CC) -c Node.cpp

Linked_List.o: Linked_List.cpp
	$(CC) -c Linked_List.cpp

driver.o: driver.cpp
	$(CC) -c driver.cpp

clean:
	rm -rf *.o $(exe_file)