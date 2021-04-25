#include <iostream>
#include "Deck.hpp"

Deck::Deck() {
    this->deck = new Card[52];
    this->numCards = 52;
    InitDeck();
    srand(time(NULL));
}

Deck::Deck(const Deck& other) {
    this->deck = new Card[52];
    this->numCards = 52;

    for (int i = 0; i < other.numCards; i++) {
        this->deck[i].SetRank(other.deck[i].GetRank());
        this->deck[i].SetSuit(other.deck[i].GetSuit());
    }
}

Deck& Deck::operator=(const Deck& other) {
    if(this->deck != NULL) {
        delete [] this->deck;
        this->deck = new Card[52];
    }

    for(int i = 0; i < other.numCards; i++) {
        this->deck[i].SetRank(other.deck[i].GetRank());
        this->deck[i].SetSuit(other.deck[i].GetSuit());
    }

    return *this;
}

void Deck::InitDeck() {
    for(int i = 0; i < 52; i++) {
        this->deck[i].SetRank(i%13);
        this->deck[i].SetSuit(i%4);
    }
    this->numCards = 52;
}

void Deck::SwapCards(int i, int j) {
    Card temp;
    temp = this->deck[i];
    this->deck[i] = this->deck[j];
    this->deck[j] = temp;
}

void Deck::Shuffle() {
    for (int i = 0; i < 250; i++) {
        int x = rand() % this->numCards;
        int y = rand() % this->numCards;

        this->SwapCards(x, y);
    }
}

Card Deck::DrawCard() {
    this->numCards--;
    Card* temp = new Card[this->numCards];
    Card draw = this->deck[0];

    for (int i = (this->numCards - 1); i >= 0; i--) { // starts at top cards of both decks and iterates down until it hits bottom
        temp[i] = this->deck[i+1];
    } 

    delete [] this->deck;
    this->deck = temp;

    return draw; // return the card we just removed
}

void Deck::ReturnCard(Card card) {
    this->numCards++;
    Card* temp = new Card[this->numCards];

    for (int i = 0; i < (this->numCards - 1); i++) {
        temp[i] = this->deck[i];
    }

    temp[this->numCards-1] = card; // sets bottom-most card to returning card

    delete [] this->deck;
    this->deck = temp;

}

void Deck::Display() const {
    std::cout << "=======Deck=======" << std::endl;
    for (int i = 0; i < this->numCards; i++) {
        std::cout << this->deck[i].GetRankString() << " of " << this->deck[i].GetSuitString() << std::endl;
    }
}

Deck::~Deck() {
    delete [] this->deck;
}