#include "Super_Bat.h"

std::string Super_Bat::Percept() { return "You hear wings flapping."; }

void Super_Bat::EventTrigger() {

}

char Super_Bat::GetType() const { return this->type; }