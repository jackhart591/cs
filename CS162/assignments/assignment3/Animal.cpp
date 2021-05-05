#include <iostream>
#include "Animal.hpp"

Animal::Animal() {
    this->age = 0;
    this->lastFoodCost = 0;
    srand(time(NULL));
}

void Animal::AdvanceAge() {
    this->age++;
}

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

int Animal::Sickness() { 

    int cost = this->cost;

    if (this->age < 5) {
        cost *= 2;
    }    
    
    return cost/2; 
}

virtual int Animal::GetRevenue() {

    int revenue = this->cost;

    if (this->age < 5) {
        revenue *= 2;
    }

    return revenue * 0.1;
}

char Animal::GetAgeStatus() {
    if (this->age < 5) {
        return 'B';
    } else if (this->age >= 48) {
        return 'A';
    } else {
        return 'T';
    }
}

int Animal::GetAge() { return this->age; }