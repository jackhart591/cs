#pragma once

class Card {
    private:
        char suit;
        int rank;

    public:
        void SetCard(char, int);
        std::string GetSuit();
        std::string GetRank();

};

// Seperate into seperate headers for assignment

class Deck {
    private:
        Card* deck;

    public:
        Deck();
        ~Deck();
        
        void CreateDeck();
        void Shuffle();
        void Print();
};

class Hand {
    private:
        Card* hand;
        int numCards;

    public:
        Hand();

        //big three
        Hand(const Hand&);
        Hand& operator=(const Hand&);
        ~Hand();
        void CreateHand();
        void SetHand(char, int);
        void DisplayHand();
};