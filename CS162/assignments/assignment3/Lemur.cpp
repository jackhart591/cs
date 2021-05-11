#include "Lemur.hpp"

/*********************************************************************
** Program Filename: Lemur.cpp
** Author: Jackson Hart
** Date: 5/10/2021
** Description: Implementation of Lemur Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Lemur Constructor
** Description: sets values to appropriate lemur standards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: values will be lemur-like
*********************************************************************/ 

Lemur::Lemur() {
    this->cost = 700;
    this->numBabies = 1;
    this->foodMult = 1;
}

/*********************************************************************
** Function: GetRevenue
** Description: Gets the revenue for lemur since it's different
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Lemur::GetRevenue() {
    int revenue = this->cost;

    if (this->age < 5) {
        revenue *= 2;
    }

    return revenue * 0.2;
}

/*********************************************************************
** Function: GetFoodCost
** Description: Gets the food with the food quality in mind
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Lemur::GetFoodCost() { return this->GetBaseFoodCost(this->foodMult); }