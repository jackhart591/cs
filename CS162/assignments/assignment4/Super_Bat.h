#pragma once
#include "Event.h"

class Super_Bat : public Event {
private:
    int stuff;

protected:
    virtual void EventTrigger() override;

public:
    Super_Bat() : Event('B') {};
    virtual ~Super_Bat() {};
    virtual void Percept() override;
    virtual char GetType() const override;
};