#include <iostream>
#include "Deck.hpp"

/*********************************************************************
** Program Filename: Deck.cpp
** Author: Jackson Hart
** Date: 4/25/2021
** Description: Implementation of Deck Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Deck Constructor
** Description: initializes deck and num cards, also runs InitDeck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: deck and num cards will be initialized with values
*********************************************************************/ 

Deck::Deck() {
    this->deck = new Card[52];
    this->numCards = 52;
    InitDeck();
}

/*********************************************************************
** Function: Deck copy constructor
** Description: initializes needed values and then copys data over
** Parameters: the deck to be copied
** Pre-Conditions: none
** Post-Conditions: deck instance will have values equal to parameter
*********************************************************************/ 

Deck::Deck(const Deck& other) {
    this->deck = new Card[52];
    this->numCards = 52;

    for (int i = 0; i < other.numCards; i++) {
        this->deck[i].SetRank(other.deck[i].GetRank());
        this->deck[i].SetSuit(other.deck[i].GetSuit());
    }
}

/*********************************************************************
** Function: Deck assignment operator overloader
** Description: copies data in parameters over to instance of deck
** Parameters: deck to be copied
** Pre-Conditions: instance of deck has to have been initialized
** Post-Conditions: instance of deck's values will be equal to
**                  paramter
*********************************************************************/ 

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

/*********************************************************************
** Function: InitDeck
** Description: initializes deck with proper suit and rank values
** Parameters: none
** Pre-Conditions: deck instance has to be initialized
** Post-Conditions: deck will have one of each card in it's values
*********************************************************************/ 

void Deck::InitDeck() {
    for(int i = 0; i < 52; i++) {
        this->deck[i].SetRank(i%13);
        this->deck[i].SetSuit(i%4);
    }
    this->numCards = 52;
}

/*********************************************************************
** Function: SwapCards
** Description: swaps two cards
** Parameters: two indexes to be swapped
** Pre-Conditions: instance of deck must be initialized
** Post-Conditions: index values i and j will have been swapped
*********************************************************************/ 

void Deck::SwapCards(int i, int j) {
    Card temp;
    temp = this->deck[i];
    this->deck[i] = this->deck[j];
    this->deck[j] = temp;
}

/*********************************************************************
** Function: Shuffle
** Description: swaps random sets of cards 250 times
** Parameters: none
** Pre-Conditions: instance of deck must have been initialized
** Post-Conditions: instance of deck will be shuffled
*********************************************************************/ 

void Deck::Shuffle() {
    for (int i = 0; i < 250; i++) {
        int x = rand() % this->numCards;
        int y = rand() % this->numCards;

        this->SwapCards(x, y);
    }
}

/*********************************************************************
** Function: DrawCard
** Description: resizes instance of deck array and takes out top card,
**              which it returns
** Parameters: none
** Pre-Conditions: instance of deck must be initialized
** Post-Conditions: deck will be missing top card
*********************************************************************/ 

Card Deck::DrawCard() {
    this->numCards--;
    if (this->numCards > 0) {
        Card* temp = new Card[this->numCards];
        Card draw = this->deck[0];

        for (int i = (this->numCards - 1); i >= 0; i--) { // starts at top cards of both decks and iterates down until it hits bottom
            temp[i] = this->deck[i+1];
        } 

        delete [] this->deck;
        this->deck = temp;

        return draw; // return the card we just removed
    } else {
        Card draw;
        draw.SetSuit(5);
        draw.SetRank(14);
        return draw;
    }
}

/*********************************************************************
** Function: ReturnCard
** Description: returns card to deck
** Parameters: card to be returned
** Pre-Conditions: instance of deck must be initialized
** Post-Conditions: deck will have card returned as last element
*********************************************************************/ 

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

/*********************************************************************
** Function: Display
** Description: Displays card array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Deck::Display() const {
    std::cout << "=======Deck=======" << std::endl;
    for (int i = 0; i < this->numCards; i++) {
        std::cout << this->deck[i].GetRankString() << " of " << this->deck[i].GetSuitString() << std::endl;
    }
}

/*********************************************************************
** Function: GetNumCards
** Description: Gets the number of cards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Deck::GetNumCards() const {
    return this->numCards;
}

/*********************************************************************
** Function: Deck deconstructor
** Description: deletes instance of deck
** Parameters: none
** Pre-Conditions: instance of deck must have been initialized
** Post-Conditions: instance of deck will be deleted
*********************************************************************/ 

Deck::~Deck() {
    delete [] this->deck;
}