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
    int batRooms[2][2] = {{-1, -1}, {-1, -1}};
    int pitRooms[2][2] = {{-1, -1}, {-1, -1}};
    int gold[2] = {-1, -1};
    int whumpus[2] = {-1, -1};

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

    this->roomArr[gold[0]][gold[1]] = Room('G');
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

    bool dead = false;

    if (player.FireArrow()) {

        std::cout << this->playerLocY << " " << this->playerLocX << std::endl;

        switch(direc) {
        case 'w':
        case 'W':
            std::cout << direc << std::endl;
            for (int i = this->playerLocX; i > 0; i--) {
                std::cout << i << " " << this->playerLocY << std::endl;
                if (this->roomArr[i][this->playerLocY].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        case 'a':
        case 'A':
            std::cout << direc << std::endl;
            for (int i = this->playerLocY; i > 0; i--) {
                std::cout << i << " " << this->playerLocY << std::endl;
                if (this->roomArr[this->playerLocX][i].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        case 's':
        case 'S':
            std::cout << direc << std::endl;
            for (int i = this->playerLocX; i < this->dimension; i++) {
                std::cout << this->playerLocY << " " << i << std::endl;
                if (this->roomArr[i][this->playerLocY].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        case 'd':
        case 'D':
            std::cout << direc << std::endl;
            for (int i = this->playerLocY; i < this->dimension; i++) {
                std::cout << i << " " << this->playerLocY << std::endl;
                if (this->roomArr[this->playerLocX][i].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        }

        if (dead) {
            std::cout << "Hit!" << std::endl;
            //whumpus death
        } else {
            std::cout << "Clink!" << std::endl;
            //whumpus awaken
        }
    } else {
        std::cout << "Out of arrows!" << std::endl;
    }
}

void Cave::CheckPercepts() {

    for (int i = this->playerLocX-1; i <= this->playerLocX+1; i++) {
         if (i < this->dimension && i >= 0 && i != this->playerLocX) {
            std::cout << i << " " << this->playerLocY << std::endl;
            if(this->roomArr[this->playerLocY][i].GetType() != ' ') {
                std::cout << this->roomArr[this->playerLocY][i].GetEvent()->Percept() << std::endl;
            }
         }
    }

    for (int i = this->playerLocY-1; i <= this->playerLocY+1; i++) {
         if (i < this->dimension && i >= 0 && i != this->playerLocY) {
            std::cout << this->playerLocX << " " << i << std::endl;
            if(this->roomArr[i][this->playerLocX].GetType() != ' ') {
                std::cout << this->roomArr[i][this->playerLocX].GetEvent()->Percept() << std::endl;
            }
         }
    }
}