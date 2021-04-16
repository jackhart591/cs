#include <iostream>
#include "Card_Game.h"

using namespace std;

Deck::Deck() {
    deck = new Card[52];
    srand(time(NULL));
}

Deck::~Deck() {
    delete [] deck;
}

void Deck::CreateDeck() {
    for (int i = 0; i < 52; i++) {
        if (i < 13) {
            this->deck[i].SetCard('D', (i%13 + 1));
        } else if (i < 26) {
            this->deck[i].SetCard('C', (i%13 + 1));
        } else if (i < 39) {
            this->deck[i].SetCard('H', (i%13 + 1));
        } else {
            this->deck[i].SetCard('S', (i%13 + 1));
        }
    }
}

void Deck::Shuffle() {
    for(int i = 0; i < 500; i++) {
        Card temp;
        int j = rand()%52;
        int k = rand()%52;
        
        temp = this->deck[j];
        this->deck[j] = this->deck[k];
        this->deck[k] = temp;
    }
}

void Deck::Print() {
    for(int i = 0; i < 52; i++) {
        std::cout << this->deck[i].GetRank() << " of " << this->deck[i].GetSuit() << endl;
    }
}