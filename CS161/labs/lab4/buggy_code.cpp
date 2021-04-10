#include <iostream>

using namespace std;

int main(){

	int x{3}, y;
  bool again;

	cout << "x is set to: " << x << endl;

	//while again is true, prompt user for y value,
	//and output if it's >, < or = to x
	cout << "Please enter a number for y: ";
	
	again = true;
 
	while (again) {
    
    cin >> y;
    cout << endl;
    
		if (x > y) {
   
			cout << "X is greater than Y" << endl;
			cout << "would you like to input another number? (n-0, y-1)" << endl;
			cin >> again;
      
		} else if (x < y) {
   
			cout << "X is less than Y" << endl;
			cout << "would you like to input another number? (n-0, y-1)" << endl;
			cin >> again;
      
		} else {
   
      cout << "X is equal to Y" << endl;
      cout << "would you like to input another number? (n-0, y-1)" << endl;
      cin >> again;
   
    }
    
	}

	//for loop, print out the value of x for 10 times
	for (int x = 0; x < 10; x++) {
		cout << x << endl;
  }
	
	//compute and output factorial for num
  int num, sum;
	cout << "What number would you like to find the factorial for? - ";
	cin >> num;
  
  sum = num;
	for (int i = (num - 1); i > 0; i--) {
		sum *= i;
  }
	cout << sum << endl;

	//conditionals
	char myAnswer;
	cout << "Are you enjoying cs161? (y or n) " << endl;
	cin >> myAnswer;
	if(myAnswer == 'y') {
		cout << "YAY" << endl;
  } else {
		cout << "YOU WILL SOON!" << endl;
  }

	return 0;
}