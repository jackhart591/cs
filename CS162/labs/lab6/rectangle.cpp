#include "rectangle.hpp"

float Rectangle::area() const { return this->width * this->height; }

bool operator> (const Rectangle& a, const Rectangle& b) { return a.area() > b.area(); }
bool operator< (const Rectangle& a, const Rectangle& b) { return a.area() < b.area(); }