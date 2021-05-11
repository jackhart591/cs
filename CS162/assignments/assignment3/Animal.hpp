#pragma once

class Animal {
    private:
        int revenue;
        int lastFoodCost;

    protected:
        int age; // in months
        int cost;
        int numBabies;
        int foodMult;

        int GetBaseFoodCost(int);

    public:
        Animal();
        Animal& operator=(const Animal&);
        int Sickness();
        int GetAge() const;
        virtual int GetRevenue();
        char GetAgeStatus();
        void AdvanceAge();
        void SetAge(int);
        int GetCost() const;
};