#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main () {

	bool letters;
	bool upLetters;
	bool lowLetters;
	bool nums;
	bool newPassword;

	int upLettersNum;
	int lowLettersNum;
	int numsNum;

	string upLetterChar;
	srand(time(NULL));

	do {
		cout << "Do you want letters (0-no, 1-yes)? ";
		cin >> letters;

		if (letters) {

	 		cout << "Do you want uppercase letters (0-no, 1-yes)? ";
        		cin >> upLetters;

        		if (upLetters) {

                		cout << "How many letters should be uppercase? ";
                		cin >> upLettersNum;
			
				for (int i = 1; i <= upLettersNum; i++) {

					int letter = rand()%25 + 66;
					upLetterChar += letter;

				}

        		}	

        		cout << "Do you want lowercase letters (0-no, 1-yes)? ";
			cin >> lowLetters;

			if (lowLetters) {

				cout << "How many letters should be lowercase? ";
				cin >> lowLettersNum;

				for (int i = 1; i <= lowLettersNum; i++) {

                                        int letter = rand()%25 + 98;
                                        upLetterChar += letter;

                                }


			}


		}

		cout << "Do you want numbers (0-no, 1-yes)?";
		cin >> nums;

		if (nums) {

			cout << "How many characters should be numbers? ";
			cin >> numsNum;
			
			for (int i = 1; i <= numsNum; i++) {

                               	int letter = rand()%9 + 49;
                            	upLetterChar += letter;

                      	}


		}

		cout << "Password: " << upLetterChar << endl;
		cout << "Would you like to create another password (0-no, 1-yes)? ";
		cin >> newPassword;
	} while (newPassword);

	return 0;
}
