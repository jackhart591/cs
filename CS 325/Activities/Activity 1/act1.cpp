/******************************************************************************
CS 325 Activity 1
Optional template for obtaining user input and providing output
Save as act1.cpp before submitting to Gradescope
Add names of students in group
*******************************************************************************/
#include <iostream>

using namespace std;

int main() {
    int A[1000];   // array of elements <= 1000
    int num; // number of elements in the array
    cin >> num; // read in number of elements
    cin >> A[0]; // the list will have at least one element
    for (int j = 1; j < num; j++) {
        cin >> A[j];
    }

// add your code
// the largest element is next to the smallest

cout << "True";
    return 1;
// the largest element is not next to the smallest
cout << "False";
    return 0;