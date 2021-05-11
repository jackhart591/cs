#include <iostream>
#include "Tiger.hpp"
#include "BlackBear.hpp"
#include "Lemur.hpp"
#include "Zoo.hpp"

/*********************************************************************
** Program Filename: ZooTycoon.cpp
** Author: Jackson Hart
** Date: 5/10/2021
** Description: Runs all the necessary things for zoo tycoon to happen
** Input: player inputs
** Output: zoo tycoon
*********************************************************************/

using namespace std;

/*********************************************************************
** Function: main
** Description: runs the stuff
** Parameters: none
** Pre-Conditions: game has not ran
** Post-Conditions: game will have been run
*********************************************************************/ 

int main() {
    Zoo myZoo;
    cout << "Welcome to Zoo Tycoon!" << endl;
    cout << "<1> Premium Food (Costs twice as much)" << endl;
    cout << "<2> Normal Food" << endl;
    cout << "<4> Cheap Food (Costs half as much)" << endl;
    cout << "To start, which type of food would you like? - ";
    int foodQuality;
    cin >> foodQuality;
    myZoo.SetFoodQuality(foodQuality);

    cout << "You start out with 100,000 in the bank, you can buy two animals per month" << endl;
    myZoo.BuyAnimal();

    do {
        myZoo.PassTime();
    } while (!myZoo.GameOver());
}