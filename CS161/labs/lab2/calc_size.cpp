#include <iostream>
#include <cmath>

using namespace std;

int main()
{
        int choice, manChoice;
        cout << "Enter a number" <<  endl;
        cin >> choice;

        manChoice = pow(2, choice);

        cout << "Max signed: " << ((manChoice/2)-1) << endl;

        cout << "Min signed: " << ((manChoice/2)*-1) << endl;

        cout << "Max unsigned: " << (manChoice - 1) << endl;

        cout << "Min unsigned: 0" << endl;

        return 0;
}
