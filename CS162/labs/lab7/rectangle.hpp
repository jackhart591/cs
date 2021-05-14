#pragma once
#include "shape.hpp"
#include <stdexcept>

class Rectangle : public Shape {
    private:
        float width;
        float height;

    public:
        Rectangle(float c_width, float c_height) : Shape { "rectangle", "pink" },
                width { c_width }, 
                height { c_height }
            { if (width == 0 || height == 0) { throw std::invalid_argument("Invalid constructor argument"); } };

        Rectangle(float c_width, float c_height, std::string name, std::string color) : Shape { name, color },
                width { c_width }, 
                height { c_height }
            { if (width == 0 || height == 0) { throw std::invalid_argument("Invalid constructor argument"); } };

        virtual float area() const override;
};

bool operator> (const Rectangle &, const Rectangle &);
bool operator< (const Rectangle &, const Rectangle &);