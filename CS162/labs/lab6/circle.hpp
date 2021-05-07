#pragma once
#include "shape.hpp"

class Circle : public Shape {
    private:
        float radius;

    public:
        Circle(float c_radius) : Shape { "circle", "blue" },
                radius { c_radius }
            {};
        virtual float area() const override;
};