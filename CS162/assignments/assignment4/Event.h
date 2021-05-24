#pragma once
#include <iostream>
#include "Player.h"

class Event {

public:
    Event(char p_type) : type(p_type) {};
    virtual ~Event() {};
    virtual std::string Percept() = 0;
    virtual char GetType() const;
    virtual void EventTrigger(Player&) = 0;

protected:
    char type;
};