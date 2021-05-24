#include "Pit.h"

std::string Pit::Percept() { return "You feel a breeze."; }

void Pit::EventTrigger() {

}

char Pit::GetType() const { return this->type; }