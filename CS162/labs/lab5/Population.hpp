#pragma once

class Population {
    private:
        int currentPop;
        int numBirths;
        int numDeaths;

    public:
        Population(int, int, int);
        void SetPop(int);
        void SetBirths(int);
        void SetDeaths(int);
        double GetBirthRate();
        double GetDeathRate();
};