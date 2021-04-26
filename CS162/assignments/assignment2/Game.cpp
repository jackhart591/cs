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

Card Game::PlayerTurn(Card lastPlayed) {
    return this->players[0].PlayerTurn(lastPlayed, &(this->cards));
}

Card Game::CompTurn(Card lastPlayed) {
    return this->players[1].CompTurn(lastPlayed, &(this->cards));
}

Card Game::DrawFirstCard() {
    return this->cards.DrawCard();
}

int Game::CheckWin(int player) {
    for(int i = 0; i < 2; i++) {
        if (this->players[i].GetHand().GetNumCards() <= 0) {
            return i;
        }
    }

    if (this->cards.GetNumCards() <= 0) {
        if (this->players[0].GetHand().GetNumCards() > this->players[1].GetHand().GetNumCards()) {
            return 0;
        } else if (this->players[0].GetHand().GetNumCards() < this->players[1].GetHand().GetNumCards()) {
            return 1;
        } else if (this->players[0].GetHand().GetNumCards() == this->players[1].GetHand().GetNumCards()) {
            return 2;
        }
    } else {
        return 3;
    }
}