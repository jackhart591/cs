#include <iostream>
#include <string>
#include <fstream>
#include "Student_DB.h"

using namespace std;

int main() {
    ifstream f;

    f.open("inputs.txt", ios::in);

    while(!f.is_open()) {
        cout << "fuck";
        // reprompt for name
    } 

    int size;
    f >> size;

    student* studentArr = CreateStudent(size);
    GetStudentDBInfo(studentArr, size, f);
    Sort(studentArr, size);
    DeleteStudentDBInfo(studentArr);


    f.close();
    return 0;
}