#include "rectangle.hpp"

class Square : public Rectangle {
    public:
        Square(float c_length) : Rectangle { c_length, c_length } {}; 
};