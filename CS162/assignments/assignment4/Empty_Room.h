#pragma once
#include "Event.h"

class Empty_Room : public Event {
    protected:
        virtual void EventTrigger() override;
    
    public:
        Empty_Room() : Event(' ') {};
        virtual ~Empty_Room();
        virtual std::string Percept() override;
        virtual char GetType() const override;

};