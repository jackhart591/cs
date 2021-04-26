#include <iostream>
#include "Game.hpp"

using namespace std;

/*********************************************************************
** Program Filename: Crazy_Eights.cpp
** Author: Jackson Hart
** Date: 4/25/2021
** Description: Driver file for Crazy Eights game
** Input: what you would like to play
** Output: who won
*********************************************************************/

/*********************************************************************
** Function: Main
** Description: runs the program
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

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