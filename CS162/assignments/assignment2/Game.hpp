#pragma once
#include "Player.hpp"
#include "Deck.hpp"

class Game {
  private:
    Deck cards;
    Player players[2];
  public:
    void InitHands();
    void PrintHands();
    Deck GetCards();
    void ShuffleDeck();
    Card PlayerTurn(Card);
    Card CompTurn(Card);
    Card DrawFirstCard();
    int CheckWin(int);
};