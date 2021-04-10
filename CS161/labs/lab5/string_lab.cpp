#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


void get_sentence(string &s) {

	getline(cin, s);
	
	return;

}


int main() {

	string sentence;

	get_sentence(sentence);
	cout << sentence << endl;

	return 0;
}
