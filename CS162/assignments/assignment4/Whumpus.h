#pragma once
#include "Event.h"

class Whumpus : public Event {
protected:
    virtual void EventTrigger() override;

public:
    Whumpus() : Event('W') {};
    virtual std::string Percept() override;
    virtual char GetType() const override;
};