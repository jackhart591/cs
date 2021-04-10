#include <iostream>
#include <string>
#include <fstream>
#include "Student_DB.h"

using namespace std;

student* CreateStudent(int numOfStudents) {
    student* studArr = new student[numOfStudents];
    return studArr;
}

void GetStudentDBInfo(student* studArr, int numOfStudents, ifstream& f) {
    for (int i = 0; i < numOfStudents; i++) {
        f >> studArr[i].studentID;
        f >> studArr[i].firstName;
        f >> studArr[i].lastName;
        f >> studArr[i].major;
    }
}

void DeleteStudentDBInfo(student* studArr) {
    delete [] studArr;
}

void WriteDB(student* arr, int len, bool stuff) {
    if (stuff) {
        ofstream outfile("out.txt");
        outfile << "SORTED BY ID:" << endl;

        for (int i = 0; i < len; i++) {
            outfile << arr[i].studentID << " " << arr[i].firstName << " " << arr[i].lastName << " " << arr[i].major << endl;
        }
        outfile << endl;
        outfile.close();
    } else {
        ofstream outfile("out.txt", ios_base::app);
        outfile << "SORTED BY LAST NAME:" << endl;
        
        for (int i = 0; i < len; i++) {
            outfile << arr[i].lastName << " " << arr[i].firstName << " " << arr[i].studentID << " " << arr[i].major << endl;
        }
        outfile << endl;
        outfile.close();
    }
}

void Sort(student* studArr, int numOfStudents) {
    for (int i = 0; i < numOfStudents-1; i++) {
        for (int j = 0; j < numOfStudents-i-1; j++) {
            if (studArr[j].studentID > studArr[j+1].studentID) {
                student temp = studArr[j];
                studArr[j] = studArr[j+1];
                studArr[j+1] = temp;
            }
        }
    }

    WriteDB(studArr, numOfStudents, true);

    for (int i = 0; i < numOfStudents-1; i++) {
        for (int j = 0; j < numOfStudents-i-1; j++) {
            if (studArr[j].lastName > studArr[j+1].lastName) {
                student temp = studArr[j];
                studArr[j] = studArr[j+1];
                studArr[j+1] = temp;
            }
        }
    }

    WriteDB(studArr, numOfStudents, false);
}