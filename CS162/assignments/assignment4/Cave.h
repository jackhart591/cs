#pragma once
#include <iostream>
#include <vector>
#include "Room.h"
#include "Player.h"

class Cave {
private:
    std::vector< std::vector<Room> > roomArr;
    int dimension;
    int playerLocX;
    int playerLocY;
    Player player;

    void SelectRoomTypes();

public:
    Cave(int);
    void DrawCave(bool);
    void MovePlayer(char);
    void FireArrow(char);
    void CheckPercepts();
};