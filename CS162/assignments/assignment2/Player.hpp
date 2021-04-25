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

};