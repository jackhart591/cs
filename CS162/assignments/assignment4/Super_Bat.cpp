#include "Super_Bat.h"

/*********************************************************************
** Program Filename: Super_Bat.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implementation of Super_Bat Class
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

std::string Super_Bat::Percept() { return "You hear wings flapping."; }

/*********************************************************************
** Function: EventTrigger
** Description: outputs necessary strings in case of event trigger
** Parameters: reference to player
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Super_Bat::EventTrigger(Player& player) {
    std::cout << "Uh oh! You entered a room with super bats!" << std::endl;
    std::cout << "Good luck finding your way back!" << std::endl;
}

/*********************************************************************
** Function: GetType
** Description: returns the type of the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

char Super_Bat::GetType() const { return this->type; }