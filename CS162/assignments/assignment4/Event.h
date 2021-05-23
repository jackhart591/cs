#pragma once

class Event {
private:
    bool playerEnter;
    bool playerStart;

public:
    Event(char p_type) : type(p_type) { this->playerStart = false; };
    virtual ~Event() {};
    virtual void Percept() = 0;
    bool isPlayerStart() const;
    virtual char GetType() const;

protected:
    char type;

    virtual void EventTrigger() = 0;
};