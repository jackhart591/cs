#include <iostream>
#include <cstring>

/**********************************************************************************************************************
 ** Program Filename: String_Edit.cpp
 ** Author: Jackson Hart
 ** Date: 2/28/2021
 ** Description: User enters a string and then edits it based off selections 
 ** Input: A string, and which edits they'd like to do in an int
 ** Output: Edited string
 ** *******************************************************************************************************************/

using namespace std;

class SearchStringObject {

  public:
  char* cStyleString;

};

/** ********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Makes sure int input is valid
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid int input
 ** ********************************************************************************************************************/

int InputHandler() {

  int input;
  cin >> input;

  if (cin.fail()) {

    do {

      cin.clear();
      cin.ignore(256, '\n');
      cout << endl << "That wasn't a valid input, try again - ";
      cin >> input;

    } while (cin.fail());

  }

  if (input < 1 || input > 4) {

    cout << endl << "That wasn't a valid option, try again - ";
    input = InputHandler();

  } else
    return input;

}

/** ********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Makes sure string input is valid
 ** Parameters: whether this is string (can be true or false, just uses so its overrideable)
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid string input
 ** ********************************************************************************************************************/

char InputHandler(bool isString) {

  char letter;
  cin >> letter;

  if (cin.fail()) {

    do {

      cin.clear();
      cin.ignore(256, '\n');
      cout << "That wasn't a valid input, try again - ";
      cin >> letter;

    } while (cin.fail());

  }

  return letter;

}

void PrintString(char* string) {

  cout << endl << "Here is your edited string: ";
  cout << string << endl << endl;

}

/** ********************************************************************************************************************
 ** Function: PurgeString
 ** Description: Rids the string of anything other than characters
 ** Parameters: string to purge, and string size
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

char* PurgeString(char* str, int stringSize) {

  char* temp = new char[1024];
  strcpy(temp, str);

  for (int i = 0; i < strlen(temp); i++) {

    if (!(((temp[i] >= 'A') && (temp[i] <= 'Z')) || ((temp[i] >= 'a') && (temp[i] <= 'z')))) {

      strcpy(&temp[i], &temp[i + 1]);
      i--;

    }

  }

  return temp;

}

/** ********************************************************************************************************************
 ** Function: SwapLetters
 ** Description: Takes two letters, and swaps the first with the second in a string
 ** Parameters: User's inputted string and the size of that string
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void SwapLetters(char* input, int stringSize) {

  cout << "What letters would you like to swap?" << endl;
  cout << "Letter 1 - ";
  char letterOne = InputHandler(true);
  cout << endl << "Letter 2 - ";
  char letterTwo = InputHandler(true);

  for (int i = 0; i < strlen(input); i++) {

    if (input[i] == letterOne) {

      input[i] = letterTwo;

    }

  }

  PrintString(input);

}

/** ********************************************************************************************************************
 ** Function: FindFrequency
 ** Description: Determines how many times a set of words shows up in a paragraph
 ** Parameters: amount of words, words to search through, words to search with, the freqency variable, and the current
 **             iteration
 ** Pre-Conditions: none
 ** Post-Conditions: Will return the frequency of the iteration
 ** ********************************************************************************************************************/

int FindFrequency(int nWords, char* input, SearchStringObject searchWords[], int frequency, int i) {

    for (int j = 0; j < strlen(input); j++) {

    char* temp = new char[1024];
    memset(temp, '\0', 1024);

    for (int k = 0; k < strlen(searchWords[i].cStyleString); k++) {

      if ((j+k) < strlen(input)) {

        temp[k] = input[j + k];

      }

    }

    if (strcmp(searchWords[i].cStyleString, temp) == 0) {

      frequency++;

    }

    delete [] temp;
    temp = NULL;

  }

  return frequency;

}


/** ********************************************************************************************************************
 ** Function: WordFrequency
 ** Description: Sees how many times a word shows up in the sentence
 ** Parameters: original sentence and size of string
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void WordFrequency(char* input, int stringSize) {
  
  cout << "How many words would you like to search for? - ";
  int nWords = InputHandler();
  int frequency[nWords];

  for (int i = 0; i < nWords; i++) {

    frequency[i] = 0;

  } 

  SearchStringObject searchWords[nWords];

  cin.ignore(256, '\n');
  cin.clear();
  for (int i = 0; i < nWords; i++) {

    cout << "What word would you like to search for?" << endl;
    char* temp = new char[stringSize + 1];
    cin.getline(temp, stringSize);
    searchWords[i].cStyleString = PurgeString(temp, stringSize);

    delete [] temp;
    temp = NULL;
    
  }

  input = PurgeString(input, stringSize);

  for (int i = 0; i < nWords; i++) {

    frequency[i] = FindFrequency(nWords, input, searchWords, frequency[i], i);
    cout << "The frequency of " << searchWords[i].cStyleString << " was: " << frequency[i] << endl << endl;

    delete [] searchWords[i].cStyleString;
    searchWords[i].cStyleString = NULL;

  }

  delete [] input;
  input = NULL;

}

/** ********************************************************************************************************************
 ** Function: ReverseString
 ** Description: Takes original inputted string and then reverses it
 ** Parameters: User's inputted string and the size of that string
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void ReverseString(char* input, int stringSize) {

  int stringLen = strlen(input);
  char* editedInput = new char[stringSize + 1];

  for (int i = 0; i < stringLen; i++)
    editedInput[i] = input[stringLen - i - 1];


  for (int i = 0; i < stringLen; i++)
    input[i] = editedInput[i];

  delete [] editedInput;

  editedInput = NULL;

  PrintString(input);

}

/** ********************************************************************************************************************
 ** Function: GetChoice
 ** Description: gets the user's choice
 ** Parameters: whether they'd like to play again, the string they're working with, and the size of the string
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void GetChoice(bool& playAgain, char* editString, int stringSize) {
  cout << "What would you like to do with the string?" << endl << "<1> Swap Two Letters" << endl << "<2> Find Frequence of a Word" << endl << "<3> Reverse the String" << endl << "<4> Quit" << endl;

  int choice = InputHandler();

  switch(choice) {

    case 1:
      SwapLetters(editString, stringSize);
      break;

    case 2:
      WordFrequency(editString, stringSize);
      break;

    case 3:
      ReverseString(editString, stringSize);
      break;

    case 4:
      playAgain = false;
      break;

    }
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: Runs the program
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

int main() {
  
  const int stringSize = 1023;
  char* userString = new char[stringSize + 1];
  char* editString = new char[stringSize + 1];

  cout << "Enter a string - " << endl;
  cin.getline(userString, stringSize);

  bool playAgain = true;

  do {

    strcpy(editString, userString);
    GetChoice(playAgain, editString, stringSize);

  } while (playAgain == true);

  delete [] userString;
  delete [] editString;

  userString = NULL;
  editString = NULL;
  
  return 0;

}