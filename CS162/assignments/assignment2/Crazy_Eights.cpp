#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
    /*Deck* gameDeck = new Deck;

    Card draw = gameDeck->DrawCard();
    gameDeck->Shuffle();
    cout << draw.GetRankString() << " of " << draw.GetSuitString() << endl;
    gameDeck->ReturnCard(draw);
    gameDeck->Display();

    delete gameDeck;*/

    Game game;
    game.InitHands();
    game.PrintHands();
    
    return 0;
}