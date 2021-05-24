#pragma once
#include "Event.h"

class Super_Bat : public Event {
private:
    int stuff;

public:
    Super_Bat() : Event('B') {};
    virtual ~Super_Bat() {};
    virtual std::string Percept() override;
    virtual char GetType() const override;
    virtual void EventTrigger(Player&) override;
};