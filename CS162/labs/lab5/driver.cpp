#include <iostream>
#include "Population.hpp"

using namespace std;

int main() {
    Population pop = Population(1000, 100, 200);
    cout << "Birth Rate: " << (double)pop.GetBirthRate() << endl;
    cout << "Death Rate: " << (double)pop.GetDeathRate() << endl;

    pop.SetPop(500);
    cout << "Birth Rate: " << (double)pop.GetBirthRate() << endl;
    cout << "Death Rate: " << (double)pop.GetDeathRate() << endl;
}