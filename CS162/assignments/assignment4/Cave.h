#pragma once
#include <iostream>
#include <vector>
#include "Room.h"

class Cave {
private:
    std::vector< std::vector<Room> > roomArr;
    //Room** roomArr;
    int dimension;

    void SelectRoomTypes();

public:
    Cave(int);
    void DrawCave(bool);
};