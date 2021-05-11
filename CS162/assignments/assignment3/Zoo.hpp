#pragma once
#include "Tiger.hpp"
#include "BlackBear.hpp"
#include "Lemur.hpp"

class Zoo {
    private:
        Tiger* tigerEx;
        BlackBear* bearEx;
        Lemur* lemurEx;
        int money;
        int numTigers, numBears, numLemurs;
        int foodQuality; // 1 for premium, 2 for normal, 4 for cheap

        bool CanHaveBabies(int);
        int Sickness(int&, int&);
        bool Birth();
        void AdvanceAnimalAges();
        void ChooseEvent();
        void Death(int, int);
        int GetRevenue();
        int GetFoodCost();

        void ResizeLemurForBirth(int);
        void ResizeTigerForBirth(int);
        void ResizeBearForBirth(int);
        void ResizeLemurForDeath(int);
        void ResizeTigerForDeath(int);
        void ResizeBearForDeath(int);

    public:
        Zoo();
        ~Zoo();
        void PassTime();
        void SetFoodQuality(int);
        void BuyAnimal();
        bool GameOver();
};