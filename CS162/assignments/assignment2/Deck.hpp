#pragma once
#include "Card.hpp"

class Deck {
    private:
        Card* deck;
        int numCards;
		void InitDeck();
		void SwapCards(int, int);
		void SwapCards(Card*, Card*);

    public:
        Deck();
        Deck(const Deck&);
        Deck& operator=(const Deck&);
        ~Deck();
        void Shuffle();
		int GetTopCard();
		Card DrawCard();
		void ReturnCard(Card);
		void Display() const;
};