#include "Cave.h"
#include <math.h>

Cave::Cave(int dimension) {
    this->dimension = dimension;
    this->roomArr = std::vector< std::vector<Room> >(dimension, std::vector<Room>(dimension)); // creates 2d vector of Rooms using parameterized constructor
    srand(time(NULL));
}

Cave::~Cave() {
    
}

void Cave::SelectRoomTypes() {
    int batRooms[2][2];
    int pitRooms[2][2];
    int gold[2];
    int whumpus[2];

    for (int i = 0; i < 2; i++) {
        do {
            batRooms[i][0] = rand() % this->dimension;
            batRooms[i][1] = rand() % this->dimension; 
        } while (this->roomArr[batRooms[i][0]][batRooms[i][1]].GetEvent().isPlayerStart());

        this->roomArr[batRooms[i][0]][batRooms[i][1]] = Room(Event::EventType::SUPER_BAT);
    }

    for (int i = 0; i < 2; i++) {
        do {
            pitRooms[i][0] = rand() % this->dimension;
            pitRooms[i][1] = rand() % this->dimension;
        } while (this->roomArr[pitRooms[i][0]][pitRooms[i][1]].GetEvent().isPlayerStart());

        this->roomArr[pitRooms[i][0]][pitRooms[i][1]] = Room(Event::EventType::PIT);
    }
}

void Cave::DrawCave(bool debug) {

    int x, y;

    for (int i = 0; i < dimension*4 + 1; i++) {
        for (int j = 0; j < dimension*4 + 1; j++) {
            x = round(x/4);
            y = round(y/4);
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
                    switch(this->roomArr[x][y].GetEvent().GetType()) {
                    case Event::EventType::PIT:
                        std::cout << "p";
                        break;
                    case Event::EventType::SUPER_BAT:
                        std::cout << "b";
                        break;
                    case Event::EventType::WHUMPUS:
                        std::cout << "w";
                        break;
                    case Event::EventType::GOLD:
                        std::cout << "g";
                        break;
                    case Event::EventType::NONE:
                        std::cout << " ";
                        break;
                    default:
                        std::cout << "E";
                        break;
                    }
                } else {
                    cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}