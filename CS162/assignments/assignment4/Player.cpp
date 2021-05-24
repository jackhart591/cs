#include "Player.h"

/*********************************************************************
** Program Filename: Player.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implimentation file for Player
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: FireArrow
** Description: Returns a bool based on whether player has enough arrows
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Player::FireArrow() {
    if (this->numArrows > 0) {
        this->numArrows--;
        return true;
    } else { return false; }
}

/*********************************************************************
** Function: HasTreasure
** Description: returns whether the player has the treasure
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Player::HasTreasure() const { return this->hasTreasure; }

/*********************************************************************
** Function: GetRemainingArrows
** Description: returns amount of remaining arrows
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Player::GetRemainingArrows() const { return this->numArrows; }

/*********************************************************************
** Function: GotTreasure
** Description: updates hasTreasure var
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Player::GotTreasure() { this->hasTreasure = true; }