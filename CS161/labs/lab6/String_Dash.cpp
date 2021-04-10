#include <iostream>
#include <string>

/** *******************************************************************************************************************
 ** Program Filename: String_Dash.cpp
 ** Author: Jackson Hart
 ** Date: 2/10/2021
 ** Description: User enters a string, program replaces all the non-space characters with dashes, user enters a
 **              character and then program replaces all the dashes with characters where that character appears in the
 **              original string
 ** Input: String and character
 ** Output: String with dashes and character and number of times the character appears
 ** *******************************************************************************************************************/

using namespace std;

/** *******************************************************************************************************************
 ** Function: get_string
 ** Description: Asks user to enter a string and then stores it in the reference
 ** Parameters: reference to string str_to_string
 ** Pre-Conditions: none
 ** Post-Conditions: str_to_store will now carry over the value to the original passed variable 
 ** ********************************************************************************************************************/
void get_string (string &str_to_store) {
  
  cout << "Enter a String: " << endl;
  getline(cin, str_to_store);
  
}

/** *******************************************************************************************************************
 ** Function: set_replace
 ** Description: changes all non-space characters to dashes
 ** Parameters: string to copy and reference to dash_str
 ** Pre-Conditions: get_str has to have to been called to get a string
 ** Post-Conditions: dash_str will now carry over the value to the original passed variable 
 ** ********************************************************************************************************************/
void set_replace (string copy_str, string &dash_str) {

  for (int i = 0; i < copy_str.length(); ++i) {
  
    if (!(copy_str[i] == 32)) {
    
      copy_str[i] = '-';
      
    }
  
  }

  dash_str = copy_str;
}


/** *******************************************************************************************************************
 ** Function: get_search_replace
 ** Description: Changes all dashes to character c where they appear in the original string
 ** Parameters: character, original string, reference to dash_str
 ** Pre-Conditions: set_replace has to have been called so dash_str is a string full of dashes
 ** Post-Conditions: dash_str will now carry over the value to the original passed variable 
 ** ********************************************************************************************************************/
int get_search_replace (char c, string copy_str, string &dash_str) {

  int bsCount = 0;

  for (int i = 0; i < copy_str.length(); ++i) {
  
    if ((copy_str[i] == c)) {
    
      dash_str[i] = c;
      bsCount++;
      
    }
  
  }

  return bsCount;
}

/** *******************************************************************************************************************
 ** Function: main
 ** Description: runs the functions
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/
int main () {

  string str_to_store, dash_str;
  char c;
  
  get_string(str_to_store);
  set_replace(str_to_store, dash_str);
  
  cout << "Enter a Character: " << endl;
  cin >> c;
  
  get_search_replace(c, str_to_store, dash_str);
  
  cout << get_search_replace(c, str_to_store, dash_str);
  cout << endl;
  cout << dash_str << endl;

  return 0;
}