CC = g++ -std=c++11 -g
exe_file = Card_Game.out

$(exe_file): Card.o Deck.o Card_Game.o
	$(CC) Card.o Deck.o Card_Game.o -o $(exe_file)

Card.o: Card.cpp
	$(CC) -c Card.cpp

Deck.o: Deck.cpp
	$(CC) -c Deck.cpp

Card_Game.o: Card_Game.cpp
	$(CC) -c Card_Game.cpp

clean:
	rm -rf *.o $(exe_file)