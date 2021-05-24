#include "Empty_Room.h"

/*********************************************************************
** Program Filename: Empty_Room.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implementation of Empty_Room Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Cave destructor
** Description: only exists to make sure program doesn't try to call 
                the event's destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Empty_Room::~Empty_Room() {}

/*********************************************************************
** Function: Percept
** Description: returns string for percept event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

std::string Empty_Room::Percept() { return "Uh oh... something went wrong!"; }

/*********************************************************************
** Function: EventTrigger
** Description: does nothing as this is an empty room
** Parameters: reference to player
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Empty_Room::EventTrigger(Player& player) {}

/*********************************************************************
** Function: GetType
** Description: returns type of this event
** Parameters: none
** Pre-Conditions: type must have been set
** Post-Conditions: none
*********************************************************************/ 

char Empty_Room::GetType() const { return this->type; }