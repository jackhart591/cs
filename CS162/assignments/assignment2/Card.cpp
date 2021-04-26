#include <iostream>
#include "Card.hpp"

/*********************************************************************
** Program Filename: Card.cpp
** Author: Jackson Hart
** Date: 4/25/2021
** Description: Implementation of Card Class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Card Constructor
** Description: sets card to default values that will be recognized as
** 				invalid
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: rank and suit will be set to 13 and 4 respectively
*********************************************************************/ 

Card::Card() {
	rank = 13;
	suit = 4;
}

/*********************************************************************
** Function: GetRank
** Description: Gets the rank of the card as an integer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Card::GetRank() const {
	return this->rank;
}

/*********************************************************************
** Function: GetSuit
** Description: Returns suit as integer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

int Card::GetSuit() const {
	return this->suit;
}

/*********************************************************************
** Function: SetRank
** Description: sets rank of card
** Parameters: rank value
** Pre-Conditions: none
** Post-Conditions: card instance will have rank equal to parameter
*********************************************************************/ 

void Card::SetRank(int rank) {
	this->rank = rank;
}

/*********************************************************************
** Function: SetSuit
** Description: sets suit of card
** Parameters: suit value
** Pre-Conditions: none
** Post-Conditions: card instance will have suit equal to parameter
*********************************************************************/ 

void Card::SetSuit(int suit) {
	if (suit > 12 || suit < 0) {
		std::cout << "That wasn't a valid rank";
		return;
	}

	this->suit = suit;
}

/*********************************************************************
** Function: SetSuit
** Description: sets suit of card
** Parameters: suit value as string
** Pre-Conditions: none
** Post-Conditions: card instance will have suit value as determined 
** 					the string
*********************************************************************/ 

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

/*********************************************************************
** Function: GetSuitString
** Description: returns suit value as string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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

/*********************************************************************
** Function: GetRankString
** Description: Gets the rank value as a string
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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
