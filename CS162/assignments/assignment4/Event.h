#pragma once
#include <iostream>

class Event {

public:
    Event(char p_type) : type(p_type) {};
    virtual ~Event() {};
    virtual std::string Percept() = 0;
    virtual char GetType() const;

protected:
    char type;

    virtual void EventTrigger() = 0;
};