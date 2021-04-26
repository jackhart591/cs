#include <iostream>
#include "Game.hpp"

using namespace std;

/*********************************************************************
** Program Filename: Game.cpp
** Author: Jackson Hart
** Date: 4/25/2021
** Description: Implementation of Game Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: InitHands
** Description: initializes hands of both players
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: instance of hands will be initialized
*********************************************************************/ 

void Game::InitHands() {
    this->players[0].GetHand().InitCards(7, &(this->cards));
    this->players[1].GetHand().InitCards(7, &(this->cards));
}

/*********************************************************************
** Function: PrintHands
** Description: prints player's hands
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Game::PrintHands() {
    for(int i = 0; i < 2; i++) {
        this->players[i].GetHand().PrintHand();
    }
}

/*********************************************************************
** Function: GetCards
** Description: returns the deck's array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Deck Game::GetCards() {
    return this->cards;
}

/*********************************************************************
** Function: ShuffleDeck
** Description: calls shuffle member function of deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: deck will be shuffled
*********************************************************************/ 

void Game::ShuffleDeck() {
    this->cards.Shuffle();
}

/*********************************************************************
** Function: SetSuit
** Description: sets suit of card
** Parameters: suit value as string
** Pre-Conditions: none
** Post-Conditions: card instance will have suit value as determined 
** 					the string
*********************************************************************/ 

Card Game::PlayerTurn(Card lastPlayed) {
    return this->players[0].PlayerTurn(lastPlayed, &(this->cards));
}

/*********************************************************************
** Function: CompTurn
** Description: lets the computer play its turn
** Parameters: the last played card
** Pre-Conditions: none
** Post-Conditions: computer will have taken its turn
*********************************************************************/ 

Card Game::CompTurn(Card lastPlayed) {
    return this->players[1].CompTurn(lastPlayed, &(this->cards));
}

/*********************************************************************
** Function: DrawFirstCard
** Description: draws the first card for the start of the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: card will have beend drawn
*********************************************************************/ 

Card Game::DrawFirstCard() {
    return this->cards.DrawCard();
}

/*********************************************************************
** Function: CheckWin
** Description: checks to see if there's any kind of win, will return 
**              a 1 if player 1 won, 2 if computer won, 3 if it's a tie
**              and 4 if it's not a win yet
** Parameters: player
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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