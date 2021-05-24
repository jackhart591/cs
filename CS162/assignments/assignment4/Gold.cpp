#include "Gold.h"

/*********************************************************************
** Program Filename: Gold.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implementation of Gold Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: EventTrigger
** Description: outputs necessary strings in case of event trigger
** Parameters: reference to player
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Gold::EventTrigger(Player& player) {
    std::cout << "You found the gold!!" << std::endl;
    std::cout << "Quick! Grab the treasure and escape before Whumpus finds you!" << std::endl;
    player.GotTreasure();
}

/*********************************************************************
** Function: Percept
** Description: returns percept string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

std::string Gold::Percept() { return "You see a glimmer nearby."; }

/*********************************************************************
** Function: GetType
** Description: returns the type of the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char Gold::GetType() const { return this->type; }