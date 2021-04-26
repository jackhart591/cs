#pragma once
#include "Hand.hpp"

class Player {
  private:
    Hand hand;
    std::string name;
  public:
    std::string GetName();
    void SetName(std::string);
    Hand& GetHand();
    Card PlayerTurn(Card, Deck*);
    Card CompTurn(Card, Deck*);
    bool ValidOption(Card);

};