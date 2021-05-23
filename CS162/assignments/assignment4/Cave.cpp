#include "Cave.h"
#include <math.h>

Cave::Cave(int dimension) {
    this->dimension = dimension;

    Room sampleRoom = Room(' ');
    std::vector<Room> roomVec;
    roomVec.resize(dimension, sampleRoom);

    this->roomArr.resize(dimension, roomVec);

    this->playerLocX = dimension-1;
    this->playerLocY = dimension-1;
    this->roomArr[this->playerLocX][this->playerLocY].SetHasPlayer(true);
    this->SelectRoomTypes();

    std::srand(time(NULL));
}

void Cave::SelectRoomTypes() {
    int batRooms[2][2];
    int pitRooms[2][2];
    int gold[2];
    int whumpus[2];

    for (int i = 0; i < 2; i++) {
        do {
            batRooms[i][0] = std::rand() % this->dimension;
            batRooms[i][1] = std::rand() % this->dimension;
        } while (this->roomArr[batRooms[i][0]][batRooms[i][1]].HasPlayer() || (batRooms[0][0] == batRooms[1][0] && batRooms[0][1] == batRooms[1][1]) || this->roomArr[batRooms[i][0]][batRooms[i][1]].GetType() != ' ');

        this->roomArr[batRooms[i][0]][batRooms[i][1]] = Room('B');

        do {
            pitRooms[i][0] = std::rand() % this->dimension;
            pitRooms[i][1] = std::rand() % this->dimension;
        } while (this->roomArr[pitRooms[i][0]][pitRooms[i][1]].HasPlayer() || (pitRooms[0][0] == pitRooms[1][0] && pitRooms[0][1] == pitRooms[1][1]) || this->roomArr[pitRooms[i][0]][pitRooms[i][1]].GetType() != ' ');

        this->roomArr[pitRooms[i][0]][pitRooms[i][1]] = Room('P');
    }

    do {
        whumpus[0] = std::rand() % this->dimension;
        whumpus[1] = std::rand() % this->dimension;
    } while (this->roomArr[whumpus[0]][whumpus[1]].HasPlayer() || this->roomArr[whumpus[0]][whumpus[1]].GetType() != ' ');

    this->roomArr[whumpus[0]][whumpus[1]] = Room('W');

    do {
        gold[0] = std::rand() % this->dimension;
        gold[1] = std::rand() % this->dimension;
    } while (this->roomArr[gold[0]][gold[1]].HasPlayer() || this->roomArr[gold[0]][gold[1]].GetType() != ' ');

    this->roomArr[whumpus[0]][whumpus[1]] = Room('G');
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
                } else if ((x < 4 && y < 4 && this->roomArr.at(x).at(y).HasPlayer()) && ((i%2 == 0 && i%4 != 0) && (j%2 == 0 && j%4 != 0))) {
                    std::cout << "*";
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

void Cave::MovePlayer(char direc) {
    switch (direc) {
    case 'w':
    case 'W':
        this->roomArr[playerLocY-1][playerLocX].SetPlayerRoom(this->roomArr[playerLocY][playerLocX]);
        this->playerLocY--;
        break;
    case 'a':
    case 'A':
        this->roomArr[playerLocY][playerLocX-1].SetPlayerRoom(this->roomArr[playerLocY][playerLocX]);
        this->playerLocX--;
        break;
    case 's':
    case 'S':
        this->roomArr[playerLocY+1][playerLocX].SetPlayerRoom(this->roomArr[playerLocY][playerLocX]);
        this->playerLocY++;
        break;
    case 'd':
    case 'D':
        this->roomArr[playerLocY][playerLocX+1].SetPlayerRoom(this->roomArr[playerLocY][playerLocX]);
        this->playerLocX++;
        break;
    }
}

void Cave::FireArrow(char direc) {

}