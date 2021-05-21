#pragma once
#include "Event.h"

class SuperBat : public Event {
private:
    int stuff;

protected:
    virtual void EventTrigger() override;

public:
    SuperBat();
    virtual void Percept() override;
};