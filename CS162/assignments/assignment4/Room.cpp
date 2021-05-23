#include "Room.h"

Room::Room() {
    this->event = new Empty_Room;
}

Room::Room(char type) {
    this->InitializeNewType(type);
}

Room::Room(const Room& other) {
    this->InitializeNewType(other.GetType());
}

Room& Room::operator=(const Room& other) {
    delete this->event;
    this->InitializeNewType(other.GetType());

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
    case ' ':
        this->event = new Empty_Room;
        break;
    }
}

Room::~Room() {
    if (this->event != NULL) {
        delete this->event;
        this->event = nullptr;
    }
}

char Room::GetType() const { return this->event->GetType(); }

Event* Room::GetEvent() { return this->event; }