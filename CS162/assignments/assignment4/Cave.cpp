#include "Cave.h"
#include <math.h>

/*********************************************************************
** Program Filename: Cave.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implementation of Cave Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Cave constructor
** Description: creates cave with n dimensions
** Parameters: dimension
** Pre-Conditions: none
** Post-Conditions: cave will be initialized with dimension
*********************************************************************/ 

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

    this->gameDone = false;

    std::srand(time(NULL));
}

/*********************************************************************
** Function: SelectRoomType
** Description: randomly generates rooms to set as special event rooms
** Parameters: none
** Pre-Conditions: cave has been initialized
** Post-Conditions: cave will have special events
*********************************************************************/ 

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
    whumpusLocX = whumpus[0];
    whumpusLocY = whumpus[1];

    do {
        gold[0] = std::rand() % this->dimension;
        gold[1] = std::rand() % this->dimension;
    } while (this->roomArr[gold[0]][gold[1]].HasPlayer() || this->roomArr[gold[0]][gold[1]].GetType() != ' ');

    this->roomArr[gold[0]][gold[1]] = Room('G');
}

/*********************************************************************
** Function: DrawCave
** Description: draws the cave
** Parameters: whether in debug mode
** Pre-Conditions: cave has been initialized
** Post-Conditions: none
*********************************************************************/ 

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
                } else if ((x < this->dimension && y < this->dimension && this->roomArr.at(x).at(y).HasPlayer()) && ((i%2 == 0 && i%4 != 0) && (j%2 == 0 && j%4 != 0))) {
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

/*********************************************************************
** Function: MovePlayer
** Description: moves player based on given direction
** Parameters: direction
** Pre-Conditions: cave has been initialized
** Post-Conditions: player will be moved in direction
*********************************************************************/ 

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

    if (this->playerLocY == this->dimension-1 && this->playerLocX == this->dimension-1 && this-player.HasTreasure()) {
        std::cout << "Congrats!! You successfully escaped from the lair of the whumpus. Good job!" << std::endl;
        this->gameDone = true;
    }

    this->roomArr[this->playerLocY][this->playerLocX].GetEvent()->EventTrigger(player);

    switch(this->roomArr[this->playerLocY][this->playerLocX].GetType()) {
    case 'B':
        int ranX;
        ranX = std::rand() % this->dimension;
        int ranY;
        ranY = std::rand() % this->dimension;
        this->roomArr[ranY][ranX].SetPlayerRoom(this->roomArr[this->playerLocY][this->playerLocX]);
        this->playerLocY = ranY;
        this->playerLocX = ranX;
        break;

    case 'P':
        this->gameDone = true;
        break;

    case 'W':
        this->gameDone = true;
        break;
    }
}

/*********************************************************************
** Function: FireArrow
** Description: fires arrow in given direction
** Parameters: direction
** Pre-Conditions: cave has been initialized
** Post-Conditions: none
*********************************************************************/ 

void Cave::FireArrow(char direc) {

    bool dead = false;

    if (player.FireArrow()) {
        switch(direc) {
        case 'w':
        case 'W':
            for (int i = this->playerLocX; i > 0; i--) {
                if (this->roomArr[i][this->playerLocY].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        case 'a':
        case 'A':
            for (int i = this->playerLocY; i > 0; i--) {
                if (this->roomArr[this->playerLocX][i].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        case 's':
        case 'S':
            for (int i = this->playerLocX; i < this->dimension; i++) {
                if (this->roomArr[i][this->playerLocY].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        case 'd':
        case 'D':
            for (int i = this->playerLocY; i < this->dimension; i++) {
                if (this->roomArr[this->playerLocX][i].GetType() == 'W') {
                    dead = true;
                }
            }
            break;
        }

        if (dead) {
            std::cout << "Hit!" << std::endl;
            std::cout << "You killed the whumpus!!" << std::endl;
            this->gameDone = true;
        } else {
            std::cout << "Clink!" << std::endl;
            if (this->WhumpusAwaken()) {
                this->roomArr[this->whumpusLocX][this->whumpusLocY] = Room(' ');

                this->whumpusLocX = rand() % this->dimension;
                this->whumpusLocY = rand() % this->dimension;

                this->roomArr[this->whumpusLocX][this->whumpusLocY] = Room('W');
            }
        }
    } else {
        std::cout << "Out of arrows!" << std::endl;
    }
}

/*********************************************************************
** Function: WhumpusAwaken
** Description: returns whether the whumpus has awoken
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

bool Cave::WhumpusAwaken() {
    int x;
    x = std::rand() % 100;

    if (x >= 75) {
        return true;
    } else {
        return false;
    }
}

/*********************************************************************
** Function: CheckPercepts
** Description: checks surrounding area to see if there's any percepts
                to percept
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Cave::CheckPercepts() {

    for (int i = this->playerLocX-1; i <= this->playerLocX+1; i++) {
         if (i < this->dimension && i >= 0 && i != this->playerLocX) {
            if(this->roomArr[this->playerLocY][i].GetType() != ' ') {
                std::cout << this->roomArr[this->playerLocY][i].GetEvent()->Percept() << std::endl;
            }
         }
    }

    for (int i = this->playerLocY-1; i <= this->playerLocY+1; i++) {
         if (i < this->dimension && i >= 0 && i != this->playerLocY) {
            if(this->roomArr[i][this->playerLocX].GetType() != ' ') {
                std::cout << this->roomArr[i][this->playerLocX].GetEvent()->Percept() << std::endl;
            }
         }
    }
}