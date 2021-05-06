#include "Lemur.hpp"

Lemur::Lemur() {
    this->cost = 700;
    this->numBabies = 1;
    this->foodMult = 1;
}

int Lemur::GetRevenue() {
    int revenue = this->cost;

    if (this->age < 5) {
        revenue *= 2;
    }

    return revenue * 0.2;
}