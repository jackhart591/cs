#pragma once
#include <iostream>

class Shape {
   private:
        std::string name;
        std::string color;
   public:
        Shape(std::string c_name, std::string c_color)
            : name { c_name },
                color { c_color }
            {};
        virtual float area() const { return 0; };
        void printShape();
};