#include "Room.h"

Room::Room() {
    this->event = new Empty_Room;
    this->hasPlayer = false;
}

Room::Room(char type) {
    this->InitializeNewType(type);
    this->hasPlayer = false;
}

Room::Room(const Room& other) {
    this->InitializeNewType(other.GetType());
    this->hasPlayer = false;
}

Room& Room::operator=(const Room& other) {
    delete this->event;
    this->InitializeNewType(other.GetType());
    this->hasPlayer = other.HasPlayer();

    return *this;
}

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