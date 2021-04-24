#include <iostream>
#include "Card_Game.h"

Hand::Hand() { // constructor
    this->hand = new Card[7];
    this->numCards = 7;
    this->CreateHand();
    std::cout << "Constructed." << std::endl;
}

Hand::Hand(const Hand& other) { // copy constructor
    std::cout << "Copy Constructor called." << std::endl;

    this->hand = new Card[7];

    for(int i = 0; i < 7; i++) {
        this->hand[i] = other.hand[i];
    }
}

void Hand::CreateHand() {
    for (int i = 0; i < 7; i++) {
        this->hand[i].SetCard('D', 1);
    }
}

Hand& Hand::operator=(const Hand& other) { // assignment overloader

    if(this->hand != NULL) {
        delete [] this->hand;
        this->hand = new Card[7];
    }

    std::cout << "Assignment Overloader called." << std::endl;
    for (int i = 0; i < 7; i++) {
        this->hand[i] = other.hand[i];
    }

    return *this;
}

Hand::~Hand() { // destructor
    std::cout << "Destructor called." << std::endl;
    delete [] this->hand;
}

void Hand::SetHand(char suit, int rank) {
    for(int i = 0; i < 7; i++) {
        this->hand[i].SetCard(suit, rank);
    }
}

void Hand::DisplayHand() {
    for (int i = 0; i < 7; i++) {
        std::cout << this->hand[i].GetSuit() << " " << this->hand[i].GetRank() << std::endl;
    }
}