#include <iostream>
#include <string>
#include <cstdlib>

/**********************************************************************************************************************
 ** Program Filename: text_adventure.cpp
 ** Author: Jackson Hart
 ** Date: 1/16/2021
 ** Description: Prompts the user in a "Choose your own adventure" type story, the user responds with either 1 or 2 to 
 **  		 choose the option they'd like when prompted. Near the end of the story, there's a fight scene in which
 ** 		 the player has to fight a goblin. This is done using a dice system to deal damage to him until he's 
 ** 		 defeated. 
 ** Input: 1, 2
 ** Output: The story's reaction to the user's decisions
 ** *******************************************************************************************************************/

using namespace std;

/*********************************************************************************************************************
 ** Function: inputHandler
 ** Description: When the program prompts the user for an answer, it calls this program to first determine what type 
 ** 		 of output the function will return and then confirms that the user's input is a valid answer
 ** Parameters: The expected datatype of the user's input
 ** Pre-Conditions: prompt the user for a question
 ** Post-Conditions: Input has been interpreted in a way the program can use 
 ** *******************************************************************************************************************/

int inputHandler (string dataType) {
	
	bool isValid = false; // Is the input a 1 or 2?
	int input = 0;

	// Cannot handle any letters

	while (!isValid) {

		input = 0;
                cin >> input;
              	if (input == 1 || input == 2) {

                      	isValid = true;

               	} else {

                	cout << "That answer is not valid, please try again" << endl;
                }

        }


	if (dataType.compare("int") == 0) {

		return input;

	} else if (dataType.compare("bool") == 0) {

		bool inputBool = (input == 1 ? true : false);
		return inputBool;

	}
}

/***********************************************************************************************************************
 ** Function: fightFunc
 ** Description: Starts a loop that rolls a dice, multiplies the roll by the damage multiplier, and then applies the
 **		 damage to the goblin. Prompts the user between each turn to enter 1 to continue, and continues until
 ** 		 the goblin is defeated. 
 ** Parameters: Whether the user picked up the weapon for the damage multiplier
 ** Pre-Conditions: Must be in the fight with the Goblin
 ** Post-Conditions: Will have defeated the Goblin
 ** ********************************************************************************************************************/

int fightFunc(bool hasWeapon) {
	
	int damage;
	double damageMult = (hasWeapon ? 1.5 : 1); // If user picked up weapon, mult = 1.5, else 1
	double goblinHealth = 20;
	srand(time(NULL));
	
	while (goblinHealth >= 0) {

		damage = rand()%19 + 1;
		if (damage == 1) {

			cout << "You roll for damage and OOFF! you roll 1!" << endl;
			cout << "With your damage multiplier you do " << damage * damageMult << " damage" << endl;
			goblinHealth -= (damage * damageMult);
			cout << "The goblin now has " << goblinHealth << " health remaining" << endl; 

		} else if (damage == 20) {

			cout << "You roll for damage and WOW! you roll 20!" << endl;
                        cout << "With your damage multiplier you do " << damage * damageMult << " damage" << endl;
                        goblinHealth -= (damage * damageMult);
                        cout << "The goblin now has " << goblinHealth << " health remaining" << endl;
		
		} else {

			cout << "You roll for damage and you roll " << damage << endl;
                        cout << "With your damage multiplier you do " << damage * damageMult << " damage" << endl;
                        goblinHealth -= (damage * damageMult);
                        cout << "The goblin now has " << goblinHealth << " health remaining" << endl;

		}
		cout << "Enter <1> to continue" << endl;
		int foo;
		cin >> foo;
	}
	return 0;	
}

/*********************************************************************************************************************
 ** Function: main
 ** Description: Main function of the program, responsible with outputting all the text for the story and calling the
 ** 		 necessary functions to handle the input and fight scene
 ** Parameters: None
 ** Pre-Conditions: None
 ** Post-Conditions: None
 ** ******************************************************************************************************************/

int main () {	

	cout << "Dungeon Adventure" << endl;
	cout << "<1> Start" << endl;
	cout << "<2> Quit" << endl;
	int startInput = inputHandler("int");
	
	if (startInput == 1) {
		
		cout << "You're face with 2 branching paths, one lit with torches," << endl;
		cout << "one pitch black, which path will you take?" << endl << endl;
		cout << "<1> Lit Path" << endl;
		cout << "<2> Unlit Path" << endl;
		int pathInput = inputHandler("int");

		if (pathInput == 1) {
			
			cout << "You walk down the lit path, eventually happening" << endl;
			cout << "upon a fallen warrior, what will you do?" << endl << endl;
			cout << "<1> Take his sword" << endl;
			cout << "<2> Leave him alone" << endl;
			bool hasSword = inputHandler("bool");
			
			if (hasSword) {

				cout << "You pick up the sword and continue along," << endl;
				cout << "eventually meeting a goblin, what will you do?" << endl << endl;
				cout << "<1> Fight Him" << endl;
				cout << "<2> Flee" << endl;
				int fightInput = inputHandler("int");

				if (fightInput == 1) {

					fightFunc(hasSword);
					cout << "Behind him is some gold, will you take it?" << endl << endl;
					cout << "<1> Take it" << endl;
					cout << "<2> Leave it" << endl;
					int goldInput = inputHandler("int");
			
					if (goldInput == 1) {

						cout << "YOU WIN!!!" << endl;

					} else {

						cout << "you lose" << endl;

					}

				} else {

					cout << "Game Over";

				}

			} else {

				cout << "You move along and eventually meet a goblin" << endl;
				cout << "What you will you do?" << endl << endl;
				cout << "<1> Fight Him" << endl;
				cout << "<2> Flee" << endl;
				int fightInput = inputHandler("int");

				if (fightInput == 1) {

					fightFunc(hasSword);
                                        cout << "Behind him is some gold, will you take it?" << endl << endl;
                                        cout << "<1> Take it" << endl;
                                        cout << "<2> Leave it" << endl;
                                        int goldInput = inputHandler("int");

                                        if (goldInput == 1) {

                                                cout << "YOU WIN!!!" << endl;

                                        } else {

                                                cout << "you lose" << endl;

                                        }


				} else {

					cout << "Game Over";

				}

			}

		} else {

			cout << "You walk down the unlit path, eventually happening" << endl;
			cout << "upon a fallen warrior, what will you do?" << endl << endl;
			cout << "<1> Take his spear" << endl;
			cout << "<2> Leave him alone" << endl;
			bool hasSpear = inputHandler("bool");
			
			if (hasSpear) {

				cout << "You pick up the sword and continue along," << endl;
                                cout << "eventually meeting a goblin, what will you do?" << endl << endl;
                                cout << "<1> Fight Him" << endl;
                                cout << "<2> Flee" << endl;
                                int fightInput = inputHandler("int");

                                if (fightInput == 1) {

                                        fightFunc(hasSpear);
                                        cout << "Behind him is some gold, will you take it?" << endl << endl;
                                        cout << "<1> Take it" << endl;
                                        cout << "<2> Leave it" << endl;
                                        int goldInput = inputHandler("int");

                                        if (goldInput == 1) {

                                                cout << "YOU WIN!!!" << endl;

                                        } else {

                                                cout << "you lose" << endl;

                                        }

                                } else {

                                        cout << "Game Over";

                                }

			} else {

				cout << "You move along and eventually meet a goblin" << endl;
                                cout << "What you will you do?" << endl << endl;
                                cout << "<1> Fight Him" << endl;
                                cout << "<2> Flee" << endl;
                                int fightInput = inputHandler("int");

                                if (fightInput == 1) {

                                        fightFunc(hasSpear);
                                        cout << "Behind him is some gold, will you take it?" << endl << endl;
                                        cout << "<1> Take it" << endl;
                                        cout << "<2> Leave it" << endl;
                                        int goldInput = inputHandler("int");

                                        if (goldInput == 1) {

                                                cout << "YOU WIN!!!" << endl;

                                        } else {

                                                cout << "you lose" << endl;

                                        }


                                } else {

                                        cout << "Game Over";

                                }

                        }						
		}
	}

	return 0;
}
