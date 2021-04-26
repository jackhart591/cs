#pragma once
#include "Deck.hpp"

class Hand {
  private:
    Card* cards;
    int numCards;
  public:   
    Hand();
    Hand(const Hand&);
    ~Hand();
    Hand& operator=(const Hand&);
    void DrawCards(int, Deck*);
    int GetNumCards() const;
    void PrintHand() const;
    void InitCards(int, Deck*);
    void PlayCard(Card);
    Card* GetCardArray();
  
};