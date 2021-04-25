#include <iostream>
#include "Card.hpp"

Card::Card() {
	rank = 13;
	suit = 4;
}

int Card::GetRank() const {
	return this->rank;
}

int Card::GetSuit() const {
	return this->suit;
}

void Card::SetRank(int rank) {
	this->rank = rank;
}

void Card::SetSuit(int suit) {
	if (suit > 12 || suit < 0) {
		std::cout << "That wasn't a valid rank";
		return;
	}

	this->suit = suit;
}

void Card::SetSuit(std::string suit) {
	if (suit.compare("hearts") == 0) {
		this->suit = 0;
	} else if (suit.compare("clubs") == 0) {
		this->suit = 1;
	} else if (suit.compare("diamonds") == 0) {
		this->suit = 2;
	} else if (suit.compare("spades") == 0) {
		this->suit = 3;
	} else {
		std::cout << "That wasn't a valid suit";
	}
}

std::string Card::GetSuitString() const {
	switch(this->suit) {
		case 0:
			return "Hearts";
			break;
		case 1:
			return "Clubs";
			break;
		case 2:
			return "Diamonds";
			break;
		case 3:
			return "Spades";
			break;
		default:
			return "ERROR: NO SUIT";
			break;
	}
} 

std::string Card::GetRankString() const {
	switch(this->rank) {
		case 0:
			return "Ace";
			break;
		case 10:
			return "Jack";
			break;
		case 11:
			return "Queen";
			break;
		case 12:
			return "King";
			break;
		default:
			return std::to_string(this->rank + 1);
			break;
	}
}
