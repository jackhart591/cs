#include "Pit.h"

/*********************************************************************
** Program Filename: Pit.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implimentation class for Pit
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Percept
** Description: returns percept string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

std::string Pit::Percept() { return "You feel a breeze."; }

/*********************************************************************
** Function: EventTrigger
** Description: outputs necessary strings in case of event trigger
** Parameters: reference to player
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Pit::EventTrigger(Player& player) {
    std::cout << "Uh oh! You fell down a pit" << std::endl;
    std::cout << "Game Over." << std::endl;
}

/*********************************************************************
** Function: GetType
** Description: returns the type of the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char Pit::GetType() const { return this->type; }