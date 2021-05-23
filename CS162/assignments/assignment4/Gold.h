#pragma once
#include "Event.h"

class Gold : public Event {
protected:
    virtual void EventTrigger() override; 

public:
    Gold() : Event('G') {};
    virtual void Percept() override;
    virtual char GetType() const override;
};