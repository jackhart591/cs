#pragma once
#include "Event.h"

class Whumpus : public Event {
public:
    Whumpus() : Event('W') {};
    virtual std::string Percept() override;
    virtual char GetType() const override;
    virtual void EventTrigger(Player&) override;
};