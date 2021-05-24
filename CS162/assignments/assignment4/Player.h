#pragma once

class Player {
private:
    int numArrows;
    bool hasTreasure;

public:
    Player() { this->numArrows = 3; this->hasTreasure = false; };
    Player(const Player& other) { this->numArrows = other.GetRemainingArrows(); }
    int GetRemainingArrows() const; 
    bool FireArrow();
    bool HasTreasure() const;
    void GotTreasure();
};