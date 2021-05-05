class Animal {
    private:
        int age; // in months
        int cost;
        int numBabies;
        int foodMult;
        int revenue;
        int lastFoodCost;

    protected:
        Animal();
        void AdvanceAge();
        int GetBaseFoodCost(int);

    public:
        int Sickness();
        int GetAge();
        virtual void GetRevenue();
        char GetAgeStatus();


};