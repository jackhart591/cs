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

    public:
        Zoo();
        ~Zoo();
        void PassTime();
        void AdvanceAnimalAges();
        void ChooseEvent();
};