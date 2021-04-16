#include <iostream>
#include "Card_Game.h"

using namespace std;

int main() {

    Deck* deck = new Deck;

    deck->CreateDeck();
    deck->Shuffle();
    deck->Print();

    delete deck;
    
    return 0;
}