#include "Cave.h"
#include <math.h>

Cave::Cave(int dimension) {
    this->dimension = dimension;

    Room sampleRoom = Room(' ');
    std::vector<Room> roomVec;
    roomVec.resize(dimension, sampleRoom);

    this->roomArr.resize(dimension, roomVec);

    std::srand(time(NULL));
}

void Cave::SelectRoomTypes() {
    int batRooms[2][2];
    int pitRooms[2][2];
    int gold[2];
    int whumpus[2];

    for (int i = 0; i < 2; i++) {
        //do {
            batRooms[i][0] = std::rand() % this->dimension;
            batRooms[i][1] = std::rand() % this->dimension;
        //} while (false /*this->roomArr[batRooms[i][0]][batRooms[i][1]].GetEvent().isPlayerStart()*/); // doesn't work!

        this->roomArr[batRooms[i][0]][batRooms[i][1]] = Room('B');
    }

    for (int i = 0; i < 2; i++) {
        //do {
            pitRooms[i][0] = std::rand() % this->dimension;
            pitRooms[i][1] = std::rand() % this->dimension;
        //} while (false/*this->roomArr[pitRooms[i][0]][pitRooms[i][1]].GetEvent().isPlayerStart()*/); // doesn't work!!

        this->roomArr[pitRooms[i][0]][pitRooms[i][1]] = Room('P');
    }
}

void Cave::DrawCave(bool debug) {

    int x, y;

    for (int i = 0; i < dimension*4 + 1; i++) {
        for (int j = 0; j < dimension*4 + 1; j++) {
            x = round(i/4);
            y = round(j/4);
            if (i % 4 == 0) {
                if (j % 4 == 0) {
                    std::cout << "+";
                } else {
                    std::cout << "-";
                }
            } else {
                if (j % 4 == 0) {
                    std::cout << "|";
                } else if (debug) {
                    std::cout << this->roomArr.at(x).at(y).GetEvent()->GetType();
                } else {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}