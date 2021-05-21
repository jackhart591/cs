#pragma once
#include "Event.h"

class Pit : public Event {
protected:
    virtual void EventTrigger() override;

public:
    Pit();
    virtual void Percept() override;
};