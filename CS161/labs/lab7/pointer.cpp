#include <iostream>
#include <string>

using namespace std;


void get_string(string *str_to_store){
  
  cout << "Enter String - ";
  getline(cin, *str_to_store);
  
}


void set_replace(string copy_str, string *dash_str){

  for (int i = 0; i < copy_str.length(); ++i){
    if (!(copy_str[i] == 32)){
      copy_str[i] = '-';
    }
  
  }

  *dash_str = copy_str;
}



int get_search_replace(char c, string copy_str, string *dash_str){

  int bsCount = 0;

  for (int i = 0; i < copy_str.length(); ++i){
    if ((copy_str[i] == c)){
      (*dash_str)[i] = c;
      bsCount++;
    }
  
  }

  return bsCount;
}


int main(){

  string str_to_store, dash_str;
  char c;
  
  get_string(&str_to_store);
  set_replace(str_to_store, &dash_str);
  
  cout << "Enter a char - ";
  cin >> c;
  cout << endl;
  
  get_search_replace(c, str_to_store, &dash_str);
  
  cout << get_search_replace(c, str_to_store, &dash_str);
  cout << "" << endl;
  cout << dash_str << endl;

  return 0;
}