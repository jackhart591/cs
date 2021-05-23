#include "Player.h"

bool Player::FireArrow() {
    if (this->numArrows > 0) {
        this->numArrows--;
        return true;
    } else { return false; }
}

int Player::GetRemainingArrows() const { return this->numArrows; }