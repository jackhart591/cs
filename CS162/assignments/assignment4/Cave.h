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
    int whumpusLocX;
    int whumpusLocY;
    Player player;
    bool gameDone;

    void SelectRoomTypes();
    bool WhumpusAwaken();

public:
    Cave(int);
    void DrawCave(bool);
    void MovePlayer(char);
    void FireArrow(char);
    void CheckPercepts();
    bool isGameDone() const { return this->gameDone; };
};