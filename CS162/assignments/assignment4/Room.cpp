#include "Room.h"

Room::Room() {
    this->event = nullptr;
}

Room::Room(Event::EventType type) {
    switch(type) {
    case Event::EventType::SUPER_BAT:
        this->event = new SuperBat;
        break;
    case Event::EventType::PIT:
        this->event = new Pit;
        break;
    }
}

Room::~Room() {
    if (this->event) {
        delete this->event;
        this->event = nullptr;
    }
}

Event& Room::GetEvent() { return *(this->event); }