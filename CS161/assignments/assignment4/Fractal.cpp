#include <iostream>

using namespace std;

/**********************************************************************************************************************
 ** Program Filename: Fractal.cpp
 ** Author: Jackson Hart
 ** Date: 2/28/2021
 ** Description: Makes a fractal to given dimensions
 ** Input: width and height
 ** Output: fractal
 ** *******************************************************************************************************************/

/** ********************************************************************************************************************
 ** Function: Pattern
 ** Description: Draws fractal pattern using recursive techniques to fit given dimensions
 ** Parameters: n and col
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void Pattern(int n, int col) {

  if (n > 0) {

    Pattern(n-2, col+1);
    
    for (int i = 0; i < (col*2); ++i) {

      cout << " ";

    }
    
    for (int i = 0; i < n; ++i) {

      cout << "* ";

    }

    cout << endl;
    Pattern(n-2, col+1);
  }
}

/** ********************************************************************************************************************
 ** Function: DetermineDimensions
 ** Description: Asks the user if they'd like to make a fractal or quit, and then runs the necessary functions
 ** Parameters: the choice the user makes
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/


void DetermineDimensions(int& choice){

  cout << "<1> Make a fractal" << endl;
  cout << "<2> Quit" << endl;
  cin >> choice; 
  
  if(choice == 1) {
  
    cout << "Enter n value: " << endl;
    int n;
    cin >> n;
    cout << "Enter col value: " << endl;
    int col;
    cin >> col;
    
    Pattern(n, col);

  }

}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: Runs the program
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

int main(){

  int x = 1;
  int y = 0;
  int z = 0;

  cout << (bool)y << endl;

  int choice;

  do {

    DetermineDimensions(choice);

  } while(choice != 0);
  
  return 0;
}
