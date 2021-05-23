#include "Empty_Room.h"

Empty_Room::~Empty_Room() {}

void Empty_Room::Percept() {

}

void Empty_Room::EventTrigger() {
    
}

char Empty_Room::GetType() const { return this->type; }