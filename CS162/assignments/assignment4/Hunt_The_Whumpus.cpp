#include <iostream>
#include <string.h>
#include "Cave.h"

using namespace std;

void ParseString(string str, Cave& cave) {

    if (str.length() > 0) {
        cave.MovePlayer(str[0]);

        if (str.length() >= 3) {
            std::cout << "Firing" << std::endl;
            cave.FireArrow(str[2]);
        }
    }
}

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cout << "ERROR: Incorrect number of args" << endl;
        return -1;
    }

    int dimension = atoi(const_cast<char*>(argv[1]));
    bool debug = strcmp(argv[2], "true") ? false : true;

    Cave caveSystem = Cave(dimension);
    bool done = false;

    do {

        caveSystem.DrawCave(debug);
        string input;
        getline(cin, input);
        ParseString(input, caveSystem);
        caveSystem.CheckPercepts();

    } while (!done);

    return 0;
}