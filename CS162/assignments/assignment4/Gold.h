#pragma once
#include "Event.h"

class Gold : public Event {

public:
    Gold() : Event('G') {};
    virtual std::string Percept() override;
    virtual char GetType() const override;
    virtual void EventTrigger(Player&) override; 
};