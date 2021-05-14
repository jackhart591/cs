#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"

using namespace std;

/*
    1. Area
    2. virtual + = 0;
    3. Yes, in fact it is
    4. Shape is an abstract base class
*/

void PrintShapeInfo(Shape& shape) {
    shape.printShape();
    cout << "Area: " << shape.area() << endl;
}

int main() {
    
    try {
        Circle circle = Circle(1);
        Rectangle rect1 = Rectangle(5, 4);
        Rectangle rect2 = Rectangle (10, 50);
        Square sq = Square(3);
        //Shape sh1 = Shape("shape", "color");

        cout << "Info for rect1: " << endl;
        PrintShapeInfo(rect1);
        cout << "\nInfo for sq: " << endl;
        PrintShapeInfo(sq);

    } catch (const invalid_argument& ia) {
        cout << "Invalid Argument: " << ia.what() << endl;
        return 0;
    }

    
    return 0;
}