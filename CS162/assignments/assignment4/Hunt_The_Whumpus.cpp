#include <iostream>
#include <string.h>
#include "Cave.h"

using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cout << "ERROR: Incorrect number of args" << endl;
        return -1;
    }

    int dimension = atoi(const_cast<char*>(argv[1]));
    bool debug = strcmp(argv[2], "true") ? false : true;

    Cave caveSystem = Cave(dimension);

    caveSystem.DrawCave(debug);

    return 0;
}