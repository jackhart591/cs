#include <iostream>
#include "Zoo.hpp"

Zoo::Zoo() {
    this->tigerEx = NULL;
    this->bearEx = NULL;
    this->lemurEx = NULL;
    this->numTigers = 0;
    this->numBears = 0;
    this->numLemurs = 0;
    std::srand(time(NULL));
}

Zoo::~Zoo() {
    delete [] this->tigerEx;
    delete [] this->bearEx;
    delete [] this->lemurEx;

    this->tigerEx = NULL;
    this->bearEx = NULL;
    this->lemurEx = NULL;
}

void Zoo::PassTime() {
    std::cout << "Advancing animal ages..." << std::endl;
    this->AdvanceAnimalAges();
    this->ChooseEvent();

}

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

bool Zoo::CanHaveBabies() {
    for (int i = 0; i < this->numTigers; i++) {
        if (this->tigerEx[i].GetAgeStatus() == 'A') {
            return true;
        }
    }

    for (int i = 0; i < this->numBears; i++) {
        if (this->bearEx[i].GetAgeStatus() == 'A') {
            return true;
        }
    }

    for (int i = 0; i < this->numLemurs; i++) {
        if (this->lemurEx[i].GetAgeStatus() == 'A') {
            return true;
        }
    }

    return false;
}

int Zoo::Sickness() {

    int i = rand() % 3;

    switch(i) {
        case 0:
            int j = rand() % this->numTigers;
            return this->tigerEx[j].Sickness();
            break;
        case 1:
            int j = rand() % this->numBears;
            return this->bearEx[j].Sickness();
            break;
        case 2:
            int j = rand() % this->numLemurs;
            return this->bearEx[j].Sickness();
            break;
    }
}

void Zoo::Birth() {

}

void Zoo::ChooseEvent() {
    int choose = (rand() % 4) + 1;

    if (choose <= this->foodQuality) {
        std::cout << "Uh oh!! One of your animals got sick!" << std::endl;
        int cost = this->Sickness();
        std::cout << "It will cost $" << cost << " to have them treated..." << std::endl;

        if(this->money >= cost) {
            std::cout << "You have enough money to pay, this amount will be subtracted from your bank account" << std::endl;
            std::cout << "Your new balance is $" << this->money << std::endl;
        } else {
            //death code
        }

    } else if (rand() % 2 == 1 && this->CanHaveBabies()) {
        //birth
    } else {
        return;
    }
}