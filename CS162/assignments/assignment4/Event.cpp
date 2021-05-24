#include "Event.h"

/*********************************************************************
** Program Filename: Event.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implementation of Event Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: GetType
** Description: returns the type of this event
** Parameters: none
** Pre-Conditions: type has been set
** Post-Conditions: none
*********************************************************************/ 

char Event::GetType() const { return this->type; }