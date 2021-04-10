#include <iostream>
#include <string>

using namespace std;

char* GetString() {

  char* userString = new char[1024];

  bool isStringValid;
  do {
  
    cout << "Enter a string - " << endl;
    cin.getline(userString, 1023);
    
    if (cin.fail()) {
    
      cin.ignore(256, '\n');
      cin.clear();
      
      cout << "That wasn't valid, try again" << endl;
      
      isStringValid = false;
    
    } else {
    
      isStringValid = true;
      
    }
  
  } while (!isStringValid);
  
  return userString;

}

string* SearchWords(int &numOfWords) {

  cout << "How many words would you like to search for? - ";
  cin >> numOfWords;
  cout << endl;
  
  string* searchWords = new string[numOfWords];
  
  cin.ignore(256, '\n');
  cin.clear();
  
  for (int i = 0; i < numOfWords; i++) {
  
    cout << "Enter word: " << endl;
    
    getline(cin, searchWords[i]);
  
  }
  
  return searchWords;

}

int main() {

  int numOfWords;
  
  char* userString = GetString();
  string* searchWords = SearchWords(numOfWords);
  
  cout << userString << endl << endl;
  
  for (int i = 0; i < numOfWords; i++) {
  
    cout << (searchWords[i]) << " ";
  
  }
  
  cout << endl;
  
  delete [] userString;
  delete [] searchWords;
  
  userString = NULL;
  searchWords = NULL;
  
  return 0;

}