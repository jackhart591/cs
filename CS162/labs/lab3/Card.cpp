#include <iostream>
#include "Card_Game.h"

void Card::SetCard(char suit, int rank) {
    this->suit = suit;
    this->rank = rank;
}

std::string Card::GetSuit() {
    switch(this->suit) {
        case 'D':
            return "Diamonds";
            break;
        case 'C':
            return "Clubs";
            break;
        case 'H':
            return "Hearts";
            break;
        case 'S':
            return "Spades";
            break;
        default:
            return "NULL";
            break;
    }
}

std::string Card::GetRank() {
    if (this->rank == 11) {return "Jack";}
    else if (this->rank == 12) {return "Queen";}
    else if (this->rank == 13) {return "King";}
    else if (this->rank == 1) {return "Ace";}
    else {
        return std::to_string(this->rank);
    }
}