#pragma once
#include "shape.hpp"
#include <stdexcept>

class Circle : public Shape {
    private:
        float radius;

    public:
        Circle(float c_radius) : Shape { "circle", "blue" },
                radius { c_radius }
            { if (radius == 0) { throw std::invalid_argument("Invalid constructor argument"); } };
        virtual float area() const override;
};