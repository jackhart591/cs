#include <iostream>
#include "Zoo.hpp"

Zoo::Zoo() {
    this->tigerEx = NULL;
    this->bearEx = NULL;
    this->lemurEx = NULL;
    this->numTigers = 0;
    this->numBears = 0;
    this->numLemurs = 0;
    srand(time(NULL));
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
    this->AdvanceAnimalAges();

}

void Zoo::AdvanceAnimalAges() {
    for (int i = 0; i < numTigers; i++) {
        tigerEx[i].AdvanceAge();
    }

    for (int i = 0; i < numBears; i++) {
        bearEx[i].AdvanceAge();
    }

    for (int i = 0; i < numLemurs; i++) {
        lemurEx[i].AdvanceAge();
    }
}

void ChooseEvent() {
    int choose = (rand() % 4) + 1;

    if (choose <= this->foodQuality) {
        //sickness
    } else if (rand() % 2 == 1) {
        //birth
    } else {
        //nothing
    }
}