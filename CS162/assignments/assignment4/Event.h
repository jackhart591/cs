#pragma once

class Event {
private:
    bool playerEnter;
    bool playerStart;

protected:
    EventType type;

    virtual void EventTrigger() = 0;

public:

    enum class EventType {
        SUPER_BAT, PIT, WHUMPUS, GOLD, NONE
    };

    Event();
    virtual void Percept() = 0;
    bool isPlayerStart();
    EventType GetType();
};