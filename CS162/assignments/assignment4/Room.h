#pragma once
#include "Event.h"
#include "Whumpus.h"
#include "Pit.h"
#include "Super_Bat.h"
#include "Gold.h"
#include "Empty_Room.h"
#include "Player.h"

class Room {
private:
    Event* event;
    char type;
    bool hasPlayer;

    void InitializeNewType(char);

public:
    Room();
    Room(char);
    Room(const Room&);
    Room& operator=(const Room&);
    ~Room();
    Event* GetEvent();
    char GetType() const;
    void SetPlayerRoom(Room&);
    void SetHasPlayer(bool);
    bool HasPlayer() const { return this->hasPlayer; };
};