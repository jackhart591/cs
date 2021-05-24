#pragma once
#include "Event.h"

class Pit : public Event {
public:
    Pit() : Event('P') {};
    virtual ~Pit() {};
    virtual std::string Percept() override;
    virtual char GetType() const override;
    virtual void EventTrigger(Player&) override;
};