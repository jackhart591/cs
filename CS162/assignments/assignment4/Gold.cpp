#include "Gold.h"

void Gold::EventTrigger() {

}

std::string Gold::Percept() { return "You see a glimmer nearby."; }

char Gold::GetType() const { return this->type; }