#include <iostream>
#include "Hand.hpp"
#include "Deck.hpp"

/*********************************************************************
** Program Filename: Hand.cpp
** Author: Jackson Hart
** Date: 4/25/2021
** Description: Implementation of Hand Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Hand Constructor
** Description: initializes hand values
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: hand instance will have been initialized
*********************************************************************/ 

Hand::Hand() {
    this->numCards = 7;
    this->cards = new Card[this->numCards];
}

/*********************************************************************
** Function: Hand Deconstructor
** Description: deletes cards array
** Parameters: none
** Pre-Conditions: instance of hand must be initialized
** Post-Conditions: cards will be deleted
*********************************************************************/ 

Hand::~Hand() {
    delete [] this->cards;
}

/*********************************************************************
** Function: InitCards
** Description: initializes cards by drawing a number of cards
** Parameters: number of cards to draw
** Pre-Conditions: none
** Post-Conditions: hand instance's card array will now be numCards
**                  long and contain new cards
*********************************************************************/ 

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

/*********************************************************************
** Function: DrawCards
** Description: draws a certain amount of cards and adds them to end
**              of card array
** Parameters: number of cards to draw and deck pointer
** Pre-Conditions: cards must have been initialized
** Post-Conditions: hand instance will now contain new cardsw
*********************************************************************/ 

void Hand::DrawCards(int numCards, Deck* deck) {
    int startingPoint = this->numCards;
    if (this->numCards < numCards) { // if the new num is larger than the hand, resizes array
        Card* temp = new Card[numCards];
        for (int i = 0; i < this->numCards; i++) {
            temp[i] = this->cards[i];
        }

        this->numCards = numCards;

        delete [] this->cards;
        this->cards = temp;
    } else {
        std::cout << "You must return your cards to the deck before assigning the hand less cards" << std::endl;
        return;
    }

    // Sets new cards to draw card's value
    for (int i = (startingPoint - 1); i < numCards; i++) {
        this->cards[i] = deck->DrawCard();
    }
}

/*********************************************************************
** Function: PlayCard
** Description: resizes array and discards card played
** Parameters: card to play
** Pre-Conditions: instance of hand must have been initialized
** Post-Conditions: specified card will be discarded
*********************************************************************/ 

void Hand::PlayCard(Card play) {
    //resizes array to minus one
    this->numCards--;
    Card* temp = new Card[this->numCards];
    int j = 0;
    for (int i = 0; i < this->numCards; i++) {
        //discards card that was passed
        if(play.GetSuit() != this->cards[j].GetSuit() || play.GetRank() != this->cards[j].GetRank()) {
            temp[i] = this->cards[j];
            j++;
        } else {j++; i--;}
    }

    delete [] this->cards;
    this->cards = temp;
}

/*********************************************************************
** Function: GetNumCards
** Description: gets number of card in hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Hand::GetNumCards() const {
    return this->numCards;
}

/*********************************************************************
** Function: PrintHand
** Description: prints instance of hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Hand::PrintHand() const {
    std::cout << "======= Hand =======" << std::endl;
    for(int i = 0; i < this->numCards; i++) {
        std::cout << "<" << i+1 << "> " << this->cards[i].GetRankString() << " of " << this->cards[i].GetSuitString() << std::endl;
    }
    std::cout << "====================" << std::endl;
}

/*********************************************************************
** Function: GetCardArray
** Description: returns instance of card array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Card* Hand::GetCardArray() {
    return this->cards;
}