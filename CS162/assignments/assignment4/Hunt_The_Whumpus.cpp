#include <iostream>
#include "Cave.h"

using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cout << "ERROR: Incorrect number of args" << endl;
        return -1;
    }

    int dimension = atoi(const_cast<char*>(argv[1]));

    Cave caveSystem = Cave(dimension);

    caveSystem.DrawCave(true);

    return 0;
}