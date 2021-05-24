#include "Room.h"

/*********************************************************************
** Program Filename: Room.cpp
** Author: Jackson Hart
** Date: 5/23/2021
** Description: Implimentation file for Room
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Room constructor
** Description: inits event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Room::Room() {
    this->event = new Empty_Room;
    this->hasPlayer = false;
}

/*********************************************************************
** Function: parameterized room constructor
** Description: inits event to specific type
** Parameters: type
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Room::Room(char type) {
    this->InitializeNewType(type);
    this->hasPlayer = false;
}

/*********************************************************************
** Function: room copy constructor
** Description: performs a deep copy
** Parameters: other room to copy from
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Room::Room(const Room& other) {
    this->InitializeNewType(other.GetType());
    this->hasPlayer = false;
}

/*********************************************************************
** Function: room assignment overloader
** Description: performs a deep copy
** Parameters: other room to copy from
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

Room& Room::operator=(const Room& other) {
    delete this->event;
    this->InitializeNewType(other.GetType());
    this->hasPlayer = other.HasPlayer();

    return *this;
}

/*********************************************************************
** Function: InitializeNewType
** Description: creates a new event based on given type
** Parameters: type
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

void Room::InitializeNewType(char type) {
    switch (type) {
    case 'B':
        this->event = new Super_Bat;
        break;
    case 'P':
        this->event = new Pit;
        break;
    case 'W':
        this->event = new Whumpus;
        break;
    case 'G':
        this->event = new Gold;
        break;
    case ' ':
        this->event = new Empty_Room;
        break;
    }
}

Room::~Room() {
    if (this->event != nullptr) {
        delete this->event;
        this->event = nullptr;
    }
}

void Room::SetHasPlayer(bool a) { this->hasPlayer = a; }

char Room::GetType() const { return this->event->GetType(); }

Event* Room::GetEvent() { return this->event; }

void Room::SetPlayerRoom(Room& pastRoom) {
    this->hasPlayer = true;
    pastRoom.SetHasPlayer(false);
}