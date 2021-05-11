#include "Tiger.hpp"

/*********************************************************************
** Program Filename: Tiger.cpp
** Author: Jackson Hart
** Date: 5/10/2021
** Description: Implementation of Tiger Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Tiger Constructor
** Description: sets values to appropriate tiger standards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: values will be tiger-like
*********************************************************************/ 

Tiger::Tiger() {
    this->cost = 15000;
    this->numBabies = 3;
    this->foodMult = 5;
}

/*********************************************************************
** Function: GetFoodCost
** Description: Gets the food with the food quality in mind
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Tiger::GetFoodCost() { return this->GetBaseFoodCost(this->foodMult); }