#include <iostream>
#include <cmath>
#include "Linked_List.h"

/*********************************************************************
** Program Filename: driver.cpp
** Author: Jackson Hart
** Date: 6/8/2021
** Description: allows user to make a list and sort it and returns the
                number of primes
** Input: values to put in and sort order
** Output: sorted list and number of primes
*********************************************************************/

/*********************************************************************
** Function: Play
** Description: runs player through entering everything and printing 
                the stuff
** Parameters: list
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template<class T>
void Play(Linked_List<T> list) {
    bool wantNum;
    do {
        T num = 0;
        std::cout << "Please enter a number: ";
        std::cin >> num;
        list.PushFront(num);
        std::cout << "Do you want another num (1 - yes, 0 - no): "; 
        std::cin >> wantNum;
    } while (wantNum);

    bool asc;
    std::cout << "Sort ascending or descending (1 - ascending 0 - descending)? ";
    std::cin >> asc;

    if (asc) { list.SortAscending(); } else { list.SortDescending(); }

    std::cout << "Your linked list is: " << std::endl;
    list.Print();
    std::cout << "You have " << list.FindNumPrimes() << " prime number(s) in your list" << std::endl;
}

/*********************************************************************
** Function: main
** Description: Initializes everything and runs play
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int main() {
    try {
        bool tryAgain = false;
        do {
            bool signedInt;
            std::cout << "Would you like to use signed or unsigned int? (1 - signed, 0 - not): ";
            std::cin >> signedInt;

            if (signedInt) {
                Linked_List<int> list;
                Play<int>(list);
            } else {
                Linked_List<unsigned int> list;
                Play<unsigned int>(list);
            }
            std::cout << "Would you like to do this again? (1 - yes, 0 - no): " << std::endl;
            std::cin >> tryAgain;
        } while (tryAgain);
    } catch (int x) {
        std::cout << "Uh Oh! Something went wrong!" << std::endl;
        return 0;
    }

    return 0;
}