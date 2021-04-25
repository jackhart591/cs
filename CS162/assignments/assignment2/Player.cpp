#include <iostream>
#include "Player.hpp"

std::string Player::GetName() {
    return this->name;
}

void Player::SetName(std::string newName) {
    this->name = newName;
}

Hand& Player::GetHand() {
    return this->hand;
}