#pragma once
#include <iostream>
#include <vector>
#include "Room.h"

class Cave {
private:
    //std::vector< std::vector<Room> > roomArr;
    int dimension;

public:
    Cave(int);
    ~Cave();
    void SelectRoomTypes();
    void DrawCave();
};