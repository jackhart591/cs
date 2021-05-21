#pragma once
#include "Event.h"
#include "Pit.h"
#include "Super_Bat.h"

class Room {
private:
    Event* event;

public:
    Room();
    Room(Event::EventType);
    ~Room();
    Event& GetEvent();
};