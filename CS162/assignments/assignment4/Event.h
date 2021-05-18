#pragma once

class Event {
private:
    bool playerEnter;
    bool playerStart;

protected:
    virtual void EventTrigger() = 0;

public:
    virtual void Percept() = 0;
    bool isPlayerStart();
};