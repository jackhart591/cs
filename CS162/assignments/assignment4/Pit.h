#pragma once
#include "Event.h"

class Pit : public Event {
protected:
    virtual void EventTrigger() override;

public:
    virtual void Percept() override;
};