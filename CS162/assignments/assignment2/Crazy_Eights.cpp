#include <iostream>
#include "Crazy_Eights.hpp"

using namespace std;

int main() {
    Deck* gameDeck = new Deck;

    Card draw = gameDeck->DrawCard();
    gameDeck->Shuffle();
    cout << draw.GetRankString() << " of " << draw.GetSuitString() << endl;
    gameDeck->ReturnCard(draw);
    gameDeck->Display();

    delete gameDeck;
    
    return 0;
}