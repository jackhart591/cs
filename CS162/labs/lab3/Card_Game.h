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