#pragma once

struct student {
    int studentID;
    std::string firstName;
    std::string lastName;
    std::string major;
};

student* CreateStudent(int);
void GetStudentDBInfo(student*, int, std::ifstream&);
void DeleteStudentDBInfo(student*);
void WriteDB(student*, int, bool);
void Sort(student*, int);