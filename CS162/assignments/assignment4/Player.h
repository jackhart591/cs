#pragma once

class Player {
private:
    int numArrows;

public:
    Player() { this->numArrows = 3; };
    Player(const Player& other) { this->numArrows = other.GetRemainingArrows(); }
    int GetRemainingArrows() const; 
    bool FireArrow();
};