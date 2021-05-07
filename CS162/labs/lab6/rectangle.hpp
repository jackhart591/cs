#pragma once
#include "shape.hpp"

class Rectangle : public Shape {
    private:
        float width;
        float height;

    public:
        Rectangle(float c_width, float c_height) : Shape { "rectangle", "blue" },
                width { c_width }, 
                height { c_height }
            {};
        virtual float area() const override;
};

bool operator> (const Rectangle &, const Rectangle &);
bool operator< (const Rectangle &, const Rectangle &);