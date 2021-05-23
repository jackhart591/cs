#pragma once
#include "Event.h"

class Pit : public Event {
protected:
    virtual void EventTrigger() override;

public:
    Pit() : Event('P') {};
    virtual ~Pit() {};
    virtual void Percept() override;
    virtual char GetType() const override;
};