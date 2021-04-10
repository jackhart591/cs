#include <iostream>
#include <ctime> /*included to allow time() to be used*/
#include <cstdlib> /*include to allow rand() and srand() to be used*/

using namespace std;

int main() {

	int x; // variable to hold our random integer
	srand(time(NULL)); // seeds random number generator. Do this just once
	
	x = rand()%5;

	if (x == 0) {

		cout << "Bummer, I'm zero!!!" << endl;

	} else if (x%2 == 1) {

		cout << "I'm an odd number!" << endl;

		switch (x) {
			case 1:
				cout << "I'm the number 1!" << endl;
				break;
			case 3:
				cout << "I'm the number 3!" << endl;
				break;
			case 5:
				cout << "I'm the number 5!" << endl;
				break;
		}

	} else {

		cout << "I'm an even number!" << endl;

		switch (x) {
			case 2:
				cout << "I'm the number 2" << endl;
				break;
			case 4:
				cout << "I'm the number 4" << endl;
				break;
		}

	}

	return 0;
}
