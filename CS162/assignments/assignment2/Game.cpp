#include <iostream>
#include "Game.hpp"

using namespace std;

void Game::InitHands() {
    this->players[0].GetHand().InitCards(7, &(this->cards));
    this->players[1].GetHand().InitCards(7, &(this->cards));
}

void Game::PrintHands() {
    for(int i = 0; i < 2; i++) {
        this->players[i].GetHand().PrintHand();
    }
}

Deck Game::GetCards() {
    return this->cards;
}

void Game::ShuffleDeck() {
    this->cards.Shuffle();
}
