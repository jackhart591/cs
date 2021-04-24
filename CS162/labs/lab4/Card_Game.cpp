#include <iostream>
#include "Card_Game.h"

using namespace std;

int main() {

    Hand hand1;
    hand1.SetHand('D', 5);
    Hand hand2 = hand1;
    hand2.DisplayHand();
    Hand hand3;
    hand3 = hand1;
    hand3.DisplayHand();

    return 0;
}