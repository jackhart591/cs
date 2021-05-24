#include "Whumpus.h"

/*********************************************************************
** Program Filename: Whumpus.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implementation of Whumpus Class
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

std::string Whumpus::Percept() { return "You smell a terrible stench."; }

/*********************************************************************
** Function: GetType
** Description: returns the type of the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

char Whumpus::GetType() const { return this->type; }

/*********************************************************************
** Function: EventTrigger
** Description: outputs necessary strings in case of event trigger
** Parameters: reference to player
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Whumpus::EventTrigger(Player& player) {
    std::cout << "You entered the horrible den of the Whumpus." << std::endl;
    std::cout << "You were mauled to death. Game over." << std::endl;
}