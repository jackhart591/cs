#pragma once
#include "Event.h"
#include "Pit.h"
#include "Super_Bat.h"
#include "Empty_Room.h"
#include <iostream>

class Room {
private:
    Event* event;
    char type;

    void InitializeNewType(char);

public:
    Room();
    Room(char);
    Room(const Room&);
    Room& operator=(const Room&);
    ~Room();
    Event* GetEvent();
    char GetType() const;
};