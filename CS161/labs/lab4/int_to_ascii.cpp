/*
Understanding the problem:
-The program must be able to take an integer and return its corresponding ascii value
-I assume that we do not have to handle bad input

Flowchart:
-take int input
-cast the type of the variable that stores the int input to a character and store that value in a variable
-return that variable in the function

Testing:
Good
4, result 99
Bad
c, result type error
*/

#include <iostream>

using namespace std;

int main() {
  
  int num;
  int hundreds, tens, ones;
  
  cout << "Enter a number - ";
  cin >> num;
  
  hundreds = num % 100;
  tens = num % 10;
  ones = num % 1;
  
  cout << endl << "Your number in ascii is - " << (char)num << endl;

  return 0; 
}