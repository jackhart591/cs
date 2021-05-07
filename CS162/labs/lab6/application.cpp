#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "square.hpp"

using namespace std;

int main() {
    Circle circle = Circle(3);
    Rectangle rect1 = Rectangle(5, 4);
    Rectangle rect2 = Rectangle (10, 50);
    Square sq = Square(3);
    Shape sh1 = Shape("shape", "color");

    cout << "Circle Area: " << circle.area() << endl;
    cout << "Rectangle Area: " << rect1.area() << endl;
    cout << "Square Area: " << sq.area() << endl;
    sh1.printShape();

    if (rect1 > rect2) {
        cout << "Rect1 is greater than Rect2!" << endl;
    } else {
        cout << "Rect2 is greater than Rect1!" << endl;
    }

    
    return 0;
}