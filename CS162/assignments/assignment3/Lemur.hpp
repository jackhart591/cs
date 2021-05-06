#pragma once
#include "Animal.hpp"

class Lemur : public Animal {
    public:
        Lemur();
        virtual int GetRevenue() override;
};