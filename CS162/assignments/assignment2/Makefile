CC = g++ -std=c++11 -Wall -g
exe_file = Crazy_Eights.out

$(exe_file): Card.o Deck.o Crazy_Eights.o
	$(CC) Card.o Deck.o Crazy_Eights.o -o $(exe_file)

Card.o: Card.cpp
	$(CC) -c Card.cpp

Deck.o: Deck.cpp
	$(CC) -c Deck.cpp

Crazy_Eights.o: Crazy_Eights.cpp
	$(CC) -c Crazy_Eights.cpp

clean:
	rm -rf *.o $(exe_file)