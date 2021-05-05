#include <iostream>
#include "Population.hpp"

Population::Population(int currentPop, int numBirths, int numDeaths) {
    this->currentPop = currentPop;
    this->numBirths = numBirths;
    this->numDeaths = numDeaths;
}

void Population::SetPop(int currentPop) {this->currentPop = currentPop;}
void Population::SetBirths(int numBirths) {this->numBirths = numBirths;}
void Population::SetDeaths(int numDeaths) {this->numDeaths = numDeaths;}

double Population::GetBirthRate() {return ((double)this->numBirths/(double)this->currentPop);}
double Population::GetDeathRate() {return ((double)this->numDeaths/(double)this->currentPop);}

