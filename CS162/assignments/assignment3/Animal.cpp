#include <iostream>
#include "Animal.hpp"

/*********************************************************************
** Program Filename: Animal.cpp
** Author: Jackson Hart
** Date: 5/10/2021
** Description: Implementation of Animal Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Animal Constructor
** Description: sets animal to default values
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: values will be useable
*********************************************************************/ 

Animal::Animal() {
    this->age = 0;
    this->lastFoodCost = 0;
    srand(time(NULL));
}

/*********************************************************************
** Function: Animal assignment operator overloader
** Description: sets values of different animals equal to eachother
** Parameters: other animal
** Pre-Conditions: none
** Post-Conditions: animals will be set equal to each other
*********************************************************************/ 

Animal& Animal::operator=(const Animal& other) {
    this->age = other.age;
    this->cost = other.cost;
    this->numBabies = other.numBabies;
    this->foodMult = other.foodMult;
    this->lastFoodCost = other.lastFoodCost;

    return *this;
}

/*********************************************************************
** Function: AdvanceAge
** Description: increments age by one month
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Animal::AdvanceAge() { this->age++; }

/*********************************************************************
** Function: GetBaseFoodCost
** Description: Gets food cost before factoring in the food quality
** Parameters: food multiplier from animal type
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Animal::GetBaseFoodCost(int foodMult) {
    if (lastFoodCost == 0) {
        this->lastFoodCost = 80;
        return this->lastFoodCost;
    } else {
        double mult = ((rand() % 120) + 80)/100;
        this->lastFoodCost *= mult;
        this->lastFoodCost *= foodMult;
        return this->lastFoodCost;
    }
}

/*********************************************************************
** Function: Sickness
** Description: calculates sickness cost
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Animal::Sickness() { 

    int cost = this->cost;

    if (this->age < 5) {
        cost *= 2;
    }
    
    return cost/2; 
}

/*********************************************************************
** Function: GetRevenue
** Description: calculates revenue of this particular animal
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Animal::GetRevenue() {

    int revenue = this->cost;

    if (this->age < 5) {
        revenue *= 2;
    }

    return revenue * 0.1;
}

/*********************************************************************
** Function: GetAgeStatus
** Description: Returns whether the animal is a baby, teen, or adult
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

char Animal::GetAgeStatus() {
    if (this->age < 5) {
        return 'B';
    } else if (this->age >= 48) {
        return 'A';
    } else {
        return 'T';
    }
}

/*********************************************************************
** Function: GetAge
** Description: Gets age
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Animal::GetAge() const { return this->age; }

/*********************************************************************
** Function: SetAge
** Description: sets age
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Animal::SetAge(int age) { this->age = age; }

/*********************************************************************
** Function: GetCost
** Description: Gets the cost
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Animal::GetCost() const { return this->cost; }