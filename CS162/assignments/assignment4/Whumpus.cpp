#include "Whumpus.h"

std::string Whumpus::Percept() { return "You smell a terrible stench."; }

char Whumpus::GetType() const { return this->type; }

void Whumpus::EventTrigger() {

}