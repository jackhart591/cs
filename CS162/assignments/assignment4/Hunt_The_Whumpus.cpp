#include <iostream>
#include <string.h>
#include "Cave.h"

using namespace std;

void ParseString(string str, Cave& cave) {

    cave.MovePlayer(str[0]);

    if (str[2] != NULL) {
        cave.FireArrow(str[2]);
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
    bool done;

    do {

        caveSystem.DrawCave(debug);
        string input;
        getline(cin, input);
        ParseString(input, caveSystem);

    } while (!done);

    return 0;
}