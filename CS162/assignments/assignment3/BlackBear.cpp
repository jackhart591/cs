#include "BlackBear.hpp"

/*********************************************************************
** Program Filename: BlackBear.cpp
** Author: Jackson Hart
** Date: 5/10/2021
** Description: Implementation of BlackBear Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: BlackBear Constructor
** Description: sets values to appropriate bear standards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: values will be bear-like
*********************************************************************/ 

BlackBear::BlackBear() {
    this->cost = 6000;
    this->numBabies = 2;
    this->foodMult = 3;
}

/*********************************************************************
** Function: GetFoodCost
** Description: Gets the food with the food quality in mind
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int BlackBear::GetFoodCost() { return this->GetBaseFoodCost(this->foodMult); }