#include <iostream>
#include "Hand.hpp"
#include "Deck.hpp"

Hand::Hand() {
    this->numCards = 7;
    this->cards = new Card[this->numCards];
}

Hand::~Hand() {
    delete [] this->cards;
}

void Hand::InitCards(int numCards, Deck* deck) {
    //resize array
    this->numCards = numCards;
    Card* temp = new Card[this->numCards];
    for (int i = 0; i < this->numCards; i++) {
        temp[i] = this->cards[i];
    }

    delete [] this->cards;
    this->cards = temp;

    //set cards to draw card
    for (int i = 0; i < this->numCards; i++) {
        this->cards[i] = deck->DrawCard();
    }
}

void Hand::DrawCards(int numCards, Deck* deck) {
    int startingPoint = this->numCards;
    if (this->numCards <= numCards) { // if the new num is larger than the hand, resizes array
        this->numCards = numCards;
        Card* temp = new Card[this->numCards];
        for (int i = 0; i < this->numCards; i++) {
            temp[i] = this->cards[i];
        }

        delete [] this->cards;
        this->cards = temp;
    } else {
        std::cout << "You must return your cards to the deck before assigning the hand less cards" << std::endl;
        return;
    }

    // Sets new cards to draw card's value
    for (int i = startingPoint; i < numCards; i++) {
        this->cards[i] = deck->DrawCard();
    }
}

int Hand::GetNumCards() const {
    return this->numCards;
}

void Hand::PrintHand() const {
    std::cout << "===== Hand =======" << std::endl;
    for(int i = 0; i < this->numCards; i++) {
        std::cout << this->cards[i].GetRankString() << " of " << this->cards[i].GetSuitString() << std::endl;
    }
}