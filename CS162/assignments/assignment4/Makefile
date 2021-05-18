CC = g++ -std=c++11 -Wall -g
exe_file = Hunt_The_Whumpus.out

$(exe_file): Event.o Pit.o Super_Bat.o Room.o Cave.o Hunt_The_Whumpus.o
	$(CC) Event.o Pit.o Room.o Cave.o Hunt_The_Whumpus.o -o $(exe_file)

Event.o: Event.cpp
	$(CC) -c Event.cpp

Pit.o: Pit.cpp
	$(CC) -c Pit.cpp

Room.o: Room.cpp
	$(CC) -c Room.cpp

Cave.o: Cave.cpp
	$(CC) -c Cave.cpp

Super_Bat.o: Super_Bat.cpp
	$(CC) -c Super_Bat.cpp

Hunt_The_Whumpus.o: Hunt_The_Whumpus.cpp
	$(CC) -c Hunt_The_Whumpus.cpp

clean:
	rm -rf *.o $(exe_file)