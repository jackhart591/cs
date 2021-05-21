#include "Event.h"

Event::Event() {
    this->type = Event::EventType::NONE;
}

bool Event::isPlayerStart() { return this->playerStart; }
Event::EventType GetType() { return this->type; }