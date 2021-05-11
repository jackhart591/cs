#include <iostream>
#include "Zoo.hpp"

/*********************************************************************
** Program Filename: Zoo.cpp
** Author: Jackson Hart
** Date: 5/10/2021
** Description: Implementation of Zoo Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Zoo Constructor
** Description: sets values to appropriate zoo standards
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: values will be zoo-like
*********************************************************************/ 

Zoo::Zoo() {
    this->tigerEx = NULL;
    this->bearEx = NULL;
    this->lemurEx = NULL;
    this->numTigers = 0;
    this->numBears = 0;
    this->numLemurs = 0;
    this->money = 100000;
    std::srand(time(NULL));
}

/*********************************************************************
** Function: Zoo deconstructor
** Description: deletes dynamic values
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Zoo::~Zoo() {
    delete [] this->tigerEx;
    delete [] this->bearEx;
    delete [] this->lemurEx;

    this->tigerEx = NULL;
    this->bearEx = NULL;
    this->lemurEx = NULL;
}

/*********************************************************************
** Function: PassTime
** Description: Calls all neccessary functions for a month to go by
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::PassTime() {
    std::cout << "Advancing animal ages..." << std::endl;
    this->AdvanceAnimalAges();
    this->ChooseEvent();

    std::cout << "You made " << this->GetRevenue() << " this month" << std::endl;
    this->money += this->GetRevenue();
    std::cout << "Your new balance is " << this->money << std::endl;

    this->BuyAnimal();

    int foodCost = this->GetFoodCost();
    std::cout << "Your food this month will cost " << foodCost << std::endl;
    this->money -= foodCost;

}

/*********************************************************************
** Function: AdvanceAnimalAges
** Description: Increments all animal ages by one month
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::AdvanceAnimalAges() {
    for (int i = 0; i < numTigers; i++) {
        this->tigerEx[i].AdvanceAge();
    }

    for (int i = 0; i < numBears; i++) {
        this->bearEx[i].AdvanceAge();
    }

    for (int i = 0; i < numLemurs; i++) {
        this->lemurEx[i].AdvanceAge();
    }
}

/*********************************************************************
** Function: CanHaveBabies
** Description: Checks all animals of one type to see if at least one
**              can have a baby
** Parameters: the animal type
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Zoo::CanHaveBabies(int animalType) {
    switch(animalType) {
        case 0:
            for (int i = 0; i < this->numTigers; i++) {
                if (this->tigerEx[i].GetAgeStatus() == 'A') {
                    return true;
                }
            }
            return false;
            break;

        case 1:
            for (int i = 0; i < this->numBears; i++) {
                if (this->bearEx[i].GetAgeStatus() == 'A') {
                    return true;
                }
            }
            return false;
            break;
    
        case 2:
            for (int i = 0; i < this->numLemurs; i++) {
                if (this->lemurEx[i].GetAgeStatus() == 'A') {
                    return true;
                }
            }
            return false;
            break;
        
        default:
            std::cout << "Got garbage value" << std::endl;
            return false;
            break;
    }
}

/*********************************************************************
** Function: Sickness
** Description: Randomly selects animal to be sick and then returns 
**              the cost of the sickness
** Parameters: animalType, and animalIndex references in case they die
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Zoo::Sickness(int& animalType, int& animalIndex) {

    animalType = std::rand() % 3;

    if (animalType == 0 && this->numTigers == 0) {
        std::cout << "Magically Cured!" << std::endl;
        return 0;
    }

    if (animalType == 1 && this->numBears == 0) {
        std::cout << "Magically Cured!" << std::endl;
        return 0;
    }

    if (animalType == 2 && this->numLemurs == 0) {
        std::cout << "Magically Cured!" << std::endl;
        return 0;
    }

    switch(animalType) {
        case 0:
            animalIndex = rand() % this->numTigers;
            return this->tigerEx[animalIndex].Sickness();
            break;
        case 1:
            animalIndex = rand() % this->numBears;
            return this->bearEx[animalIndex].Sickness();
            break;
        case 2:
            animalIndex = rand() % this->numLemurs;
            return this->lemurEx[animalIndex].Sickness();
            break;
        default:
            return -1;
            break;
    }
}

/*********************************************************************
** Function: ResizeTigerForDeath
** Description: Resizes Tiger array for death
** Parameters: the animal index of dying tiger
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ResizeTigerForDeath(int animalIndex) {
    Tiger* temp = new Tiger[this->numTigers - 1];
    int j = 0;
    for (int i = 0; i < this->numTigers; i++) {
        if (i != animalIndex) {
            temp[j] = this->tigerEx[i];
        } else {j--;}
        j++;
    }

    this->numTigers--;
    delete [] this->tigerEx;
    this->tigerEx = temp;
}

/*********************************************************************
** Function: ResizeBearForDeath
** Description: Resizes Bear array for death
** Parameters: the animal index of dying Bear
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ResizeBearForDeath(int animalIndex) {
    BlackBear* temp = new BlackBear[this->numBears - 1];
    int j = 0;
    for (int i = 0; i < this->numBears; i++) {
        if (i != animalIndex) {
            temp[j] = this->bearEx[i];
        } else {j--;}
        j++;
    }

    this->numBears--;
    delete [] this->bearEx;
    this->bearEx = temp;
}

/*********************************************************************
** Function: ResizeLemurForDeath
** Description: Resizes Lemur array for death
** Parameters: the animal index of dying lemur
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ResizeLemurForDeath(int animalIndex) {
    Lemur* temp = new Lemur[this->numLemurs - 1];
    int j = 0;
    for (int i = 0; i < this->numLemurs; i++) {
        if (i != animalIndex) {
            temp[j] = this->lemurEx[i];
        } else {j--;}
        j++;
    }

    this->numLemurs--;
    delete [] this->lemurEx;
    this->lemurEx = temp;
}

/*********************************************************************
** Function: ResizeTigerForBirth
** Description: Resizes Tiger array for birth/buying
** Parameters: the age of the animal being "birthed"
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ResizeTigerForBirth(int age) {
    Tiger* temp = new Tiger[this->numTigers + 1];
    for (int i = 0; i < this->numTigers; i++) {
        temp[i] = this->tigerEx[i];
    }

    this->numTigers++;
    Tiger newTiger;
    newTiger.SetAge(age);
    temp[this->numTigers - 1] = newTiger;

    delete [] this->tigerEx;
    this->tigerEx = temp;
}

/*********************************************************************
** Function: ResizeBearForBirth
** Description: Resizes Bear array for birth/buying
** Parameters: the age of the animal being "birthed"
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ResizeBearForBirth(int age) {
    BlackBear* temp = new BlackBear[this->numBears + 1];
    for (int i = 0; i < this->numBears; i++) {
        temp[i] = this->bearEx[i];
    }

    this->numBears++;
    BlackBear newBear;
    newBear.SetAge(age);
    temp[this->numBears - 1] = newBear;

    delete [] this->bearEx;
    this->bearEx = temp;
}

/*********************************************************************
** Function: ResizeLemurForBirth
** Description: Resizes Lemur array for birth/buying
** Parameters: the age of the animal being "birthed"
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ResizeLemurForBirth(int age) {
    Lemur* temp = new Lemur[this->numLemurs + 1];
    for (int i = 0; i < this->numLemurs; i++) {
        temp[i] = this->lemurEx[i];
    }

    this->numLemurs++;
    Lemur newLemur;
    newLemur.SetAge(age);
    temp[this->numLemurs - 1] = newLemur;

    delete [] this->lemurEx;
    this->lemurEx = temp;
}

/*********************************************************************
** Function: Birth
** Description: randomly selects eligible animal to give birth
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Zoo::Birth() {
    int animalType = std::rand() % 3;

    Tiger newTiger;
    BlackBear newBear;
    Lemur newLemur;

    if (this->CanHaveBabies(animalType)) {
        std::cout << "One of your animals is having a baby..." << std::endl;
        switch(animalType) {
            case 0:
                std::cout << "A tiger has been born!" << std::endl;
                ResizeTigerForBirth(0);
                return true;
            case 1:
                std::cout << "A bear has been born!" << std::endl;
                ResizeBearForBirth(0);
                return true;
            case 2:
                std::cout << "A lemur has been born!" << std::endl;
                ResizeLemurForBirth(0);
                return true;
        }
    }

    return false;
}

/*********************************************************************
** Function: Death
** Description: calls necessary functions to start process of death
** Parameters: animal type and index to die
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::Death(int animalType, int animalIndex) {
    switch (animalType) {
        case 0:
            ResizeTigerForDeath(animalIndex);
            break;
        case 1:
            ResizeBearForDeath(animalIndex);
            break;
        case 2:
            ResizeLemurForDeath(animalIndex);
            break;
        case -1:
            std::cout << "Got garbage value" << std::endl;
    }
}

/*********************************************************************
** Function: ChooseEvent
** Description: randomly selects appropriate event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::ChooseEvent() {
    int choose = (std::rand() % 4) + 1;

    int animalType = -1;
    int animalIndex = -1;

    if (choose <= this->foodQuality) {
        std::cout << "Uh oh!! One of your animals got sick!" << std::endl;
        int cost = this->Sickness(animalType, animalIndex);
        std::cout << "It will cost $" << cost << " to have them treated..." << std::endl;

        if(this->money >= cost) {
            std::cout << "You have enough money to pay, this amount will be subtracted from your bank account" << std::endl;
            std::cout << "Your new balance is $" << this->money << std::endl;
        } else {
            std::cout << "Your animal died, too bad!" << std::endl;
            this->Death(animalType, animalIndex);
        }

    } else if (rand() % 2 == 1 && this->Birth()) {} else {
        return;
    }
}

/*********************************************************************
** Function: SetFoodQuality
** Description: sets the food quality
** Parameters: food quality
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::SetFoodQuality(int x) { this->foodQuality = x; }

/*********************************************************************
** Function: BuyAnimal
** Description: asks user if they want to buy an animal
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Zoo::BuyAnimal() {
    std::cout << "<1> Tiger" << std::endl;
    std::cout << "<2> Black Bear" << std::endl;
    std::cout << "<3> Lemur" << std::endl;
    std::cout << "<4> None" << std::endl;
    std::cout << "Would you like to buy an animal? - ";

    int animalSelection;
    std::cin >> animalSelection;

    int numAnimals;
    if (animalSelection != 4) {
        do {
        std::cout << "How many? 1 or 2 - ";
        std::cin >> numAnimals;
        } while (numAnimals != 1 && numAnimals != 2);
    }

    Tiger newTiger;
    newTiger.SetAge(48);
    BlackBear newBear;
    newBear.SetAge(48);
    Lemur newLemur;
    newLemur.SetAge(48);

    switch(animalSelection) {
        case 1:
            for (int i = 0; i < numAnimals; i++) { 
                ResizeTigerForBirth(48); 
                this->money -= this->tigerEx[0].GetCost();
            }
            break;
        case 2:
            for (int i = 0; i < numAnimals; i++) { 
                ResizeBearForBirth(48); 
                this->money -= this->bearEx[0].GetCost();
            }
            break;
        case 3:
            for (int i = 0; i < numAnimals; i++) { 
                ResizeLemurForBirth(48);
                this->money -= this->lemurEx[0].GetCost();
            }
            break;
    }
}

/*********************************************************************
** Function: GetRevenue
** Description: Gets the total revenue from every animal
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Zoo::GetRevenue() {
    int revenue = 0;

    for(int i = 0; i < this->numTigers; i++) {
        revenue += this->tigerEx[i].GetRevenue();
    }

    for (int i = 0; i < this->numBears; i++) {
        revenue += this->bearEx[i].GetRevenue();
    }

    for (int i = 0; i < this->numLemurs; i++) {
        revenue += this->lemurEx[i].GetRevenue();
    }

    return revenue;
}

/*********************************************************************
** Function: GetFoodCost
** Description: gets total food cost from every animal
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Zoo::GetFoodCost() {
    int foodCost = 0;

    for(int i = 0; i < this->numTigers; i++) {
        foodCost += this->tigerEx[i].GetFoodCost();
    }

    for (int i = 0; i < this->numBears; i++) {
        foodCost += this->bearEx[i].GetFoodCost();
    }

    for (int i = 0; i < this->numLemurs; i++) {
        foodCost += this->lemurEx[i].GetFoodCost();
    }

    return foodCost;
}

/*********************************************************************
** Function: GameOver
** Description: checks to see if either out of money or if player 
**              wants to quit
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Zoo::GameOver() {
    if (this->money <= 0) {
        std::cout << "Uh oh, you ran out of money! Game Over" << std::endl;
        return true;
    } else {
        std::cout << "Would you like to keep playing or quit? (0 for keep playing, 1 for quit) ";
        bool quit;
        std::cin >> quit;
        return quit;
    }
}