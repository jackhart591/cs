#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
    
    bool playAgain;
    do {
        Game game;
        game.ShuffleDeck();
        game.InitHands();

        Card lastPlayed; 
        lastPlayed = game.DrawFirstCard();

        int win = 3;

        do {
            cout << "Player 1's turn..." << endl;
            lastPlayed = game.PlayerTurn(lastPlayed);

            if (game.CheckWin(0) != 3) {
                win = game.CheckWin(0);
                break;
            }

            cout << "Player 2's turn..." << endl;
            lastPlayed = game.CompTurn(lastPlayed);
            win = game.CheckWin(1);
        } while (win == 3);

        switch(win) {
            case 0:
                cout << "Player 1 wins!" << endl;
                break;
            case 1:
                cout << "Player 2 wins!" << endl;
                break;
            case 2:
                cout << "The game is a tie!" << endl;
                break;
        }

        cout << "Would you like to play again? (0 - yes, 1 - no) - "; 
        cin >> playAgain;
    } while (!playAgain);
    
    return 0;
}