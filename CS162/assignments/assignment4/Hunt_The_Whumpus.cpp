#include <iostream>
#include <string.h>
#include "Cave.h"

using namespace std;

/*********************************************************************
** Program Filename: Hunt_The_Whumpus.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Driver class for hunt the whumpus
** Input: game input
** Output: game
*********************************************************************/

/*********************************************************************
** Function: ParseString
** Description: parses the string and calls necessary functions
** Parameters: str to parse, cave reference
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void ParseString(string str, Cave& cave) {

    if (str.length() > 0) {
        cave.MovePlayer(str[0]);

        if (str.length() >= 3) {
            std::cout << "Firing..." << std::endl;
            cave.FireArrow(str[2]);
        }
    }
}

/*********************************************************************
** Function: Main
** Description: runs everything
** Parameters: num args, arg array
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cout << "ERROR: Incorrect number of args" << endl;
        return -1;
    }

    int dimension = atoi(const_cast<char*>(argv[1]));
    bool debug = strcmp(argv[2], "true") ? false : true;

    Cave caveSystem = Cave(dimension);

    do {

        caveSystem.DrawCave(debug);
        string input;
        getline(cin, input);
        ParseString(input, caveSystem);
        caveSystem.CheckPercepts();

    } while (!caveSystem.isGameDone());

    return 0;
}