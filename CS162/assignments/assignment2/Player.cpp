#include <iostream>
#include "Player.hpp"

/*********************************************************************
** Program Filename: Player.cpp
** Author: Jackson Hart
** Date: 4/25/2021
** Description: Implementation of Player Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: GetName
** Description: gets name of player
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

std::string Player::GetName() {
    return this->name;
}

/*********************************************************************
** Function: SetName
** Description: sets name of player instance
** Parameters: new name
** Pre-Conditions: none
** Post-Conditions: instance of player will have updated name
*********************************************************************/ 

void Player::SetName(std::string newName) {
    this->name = newName;
}

/*********************************************************************
** Function: GetHand
** Description: returns reference to player hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Hand& Player::GetHand() {
    return this->hand;
}

/*********************************************************************
** Function: ValidOption
** Description: determines if player has any options to play
** Parameters: the last played card
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Player::ValidOption(Card lastPlayed) {
    for(int i = 0; i < this->hand.GetNumCards(); i++) {
        if (this->hand.GetCardArray()[i].GetSuit() == lastPlayed.GetSuit() || this->hand.GetCardArray()[i].GetRank() == lastPlayed.GetRank()) {
            return true;
        }
    }

    return false;
}

/*********************************************************************
** Function: WildCard
** Description: Determines which suit player wants to use
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: last played card will be set to suit of player's
**                  choice
*********************************************************************/ 

void Player::WildCard(int playCard) {
    std::cout << "Which Suit would you like the next player to play? (lowercase) - ";
    std::string ans;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::getline(std::cin, ans);

    this->hand.GetCardArray()[playCard].SetSuit(ans);
    this->hand.GetCardArray()[playCard].SetRank(13);
}

/*********************************************************************
** Function: DeterminePlay
** Description: Determines which card player wants to play
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Player::DeterminePlay(Card lastPlayed, int playCard) {
    std::cout << "which card would you like to play? - ";
    std::cin >> playCard;
    playCard--; // correct for arrays starting at 0
    bool playCardValid = false;
    do {
        if (this->hand.GetCardArray()[playCard].GetSuit() != lastPlayed.GetSuit() && this->hand.GetCardArray()[playCard].GetRank() != lastPlayed.GetRank()) {
            std::cout << "That wasn't a valid option, try again - ";
            std::cin >> playCard;
            playCard--; 
        } else {
            playCardValid = true;
        }
    } while (!playCardValid);

    return playCard;
}

/*********************************************************************
** Function: PlayerTurn
** Description: Runs the player's turn
** Parameters: last card played and pointer to deck
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

Card Player::PlayerTurn(Card lastPlayed, Deck* deck) {
    std::cout << "Current Card on top: " << lastPlayed.GetRankString() << " of " << lastPlayed.GetSuitString() << std::endl;
    this->hand.PrintHand();
    int playCard;
    if (this->ValidOption(lastPlayed)) { // check to make sure there's at least one valid option to play
        playCard = this->DeterminePlay(lastPlayed, playCard);
        if (this->hand.GetCardArray()[playCard].GetRank() == 7) { //if player plays a "wild card"
            this->WildCard(playCard);
        }

        Card cardPlayed = this->hand.GetCardArray()[playCard];
        this->hand.PlayCard(this->hand.GetCardArray()[playCard]);
        return cardPlayed;

    } else {
        std::cout << "There is nothing you can play, so you will need to draw a card." << std::endl;
        bool playable = false;
        do {
            if (deck->GetNumCards() > 0) {
                this->hand.DrawCards(this->hand.GetNumCards() + 1, deck);

                if (this->hand.GetCardArray()[this->hand.GetNumCards() - 1].GetRank() == lastPlayed.GetRank() || this->hand.GetCardArray()[this->hand.GetNumCards() - 1].GetSuit() == lastPlayed.GetSuit() || deck->GetNumCards() <= 0) {
                    playable = true;
                }
            } else {
                return lastPlayed;
            }
        } while (!playable);
        return lastPlayed;
    }
}

/*********************************************************************
** Function: CompTurn
** Description: Lets computer take it's turn
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Card Player::CompTurn(Card lastPlayed, Deck* deck) {
    int playCard; 
    if (this->ValidOption(lastPlayed)) { // check to make sure there's at least one valid option to play
        for (int i = 0; i < this->hand.GetNumCards(); i++) {
            if (this->hand.GetCardArray()[i].GetSuit() == lastPlayed.GetSuit() || this->hand.GetCardArray()[i].GetRank() == lastPlayed.GetRank()) {
                playCard = i;
                break;
            }
        }
        Card cardPlayed = this->hand.GetCardArray()[playCard];
        this->hand.PlayCard(this->hand.GetCardArray()[playCard]);
        return cardPlayed;
    } else {
        bool playable = false;
        if (deck->GetNumCards() > 0) {
            do {
                this->hand.DrawCards(this->hand.GetNumCards() + 1, deck);

                if (this->hand.GetCardArray()[this->hand.GetNumCards() - 1].GetRank() == lastPlayed.GetRank() || this->hand.GetCardArray()[this->hand.GetNumCards() - 1].GetSuit() == lastPlayed.GetSuit() || deck->GetNumCards() <= 0) {
                    playable = true;
                }
            } while (!playable);
        }
        return lastPlayed;
    }
}