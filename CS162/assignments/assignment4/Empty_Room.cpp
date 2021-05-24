#include "Empty_Room.h"

Empty_Room::~Empty_Room() {}

std::string Empty_Room::Percept() { return "Uh oh... something went wrong!"; }

void Empty_Room::EventTrigger() {
    
}

char Empty_Room::GetType() const { return this->type; }