#pragma once
#include "Event.h"

class Empty_Room : public Event {
    public:
        Empty_Room() : Event(' ') {};
        virtual ~Empty_Room();
        virtual std::string Percept() override;
        virtual char GetType() const override;
        virtual void EventTrigger(Player&) override;

};