#include <iostream>
#include <string>
#include <fstream>
#include "Book_Sort.h"

/**********************************************************************************************************************
 ** Program Filename: Book_Sort_Driver.cpp
 ** Author: Jackson Hart
 ** Date: 4/10/2021
 ** Description: Takes in a file full of spellbooks, sorts them, and outputs them to either screen or file
 ** Input: file of spellbooks
 ** Output: sorted spells/spellbooks
 ** *******************************************************************************************************************/

using namespace std;

/** ********************************************************************************************************************
 ** Function: GetSortMethod
 ** Description: Prompts user for what they'd like to do
 ** Parameters: spellbook array, number of spellbooks
 ** Pre-Conditions: Spellbook array must've been initialized and populated
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

bool GetSortMethod(Spellbook* spellbookArr, int numSpellbooks) {
    int choice;

    cout << "<1> Sort spellbooks by number of pages" << endl;
    cout << "<2> Sort spellbooks by average rate of success" << endl;
    cout << "<3> Group spells by effect" << endl;
    cout << "<4> Quit" << endl;
    cout << "Enter what you'd like to do - ";

    cin >> choice;

    while (cin.fail() || choice > 4 || choice < 1) {
        cout << endl << "That wasn't a valid choice, try again - ";
        cin >> choice;
    }

    switch (choice) {
        case 1:
            SortByMethod("numPages", spellbookArr, numSpellbooks);
            break;
        case 2:
            SortByMethod("avgSuccess", spellbookArr, numSpellbooks);
            break;
        case 3:
            SortByMethod("effect", spellbookArr, numSpellbooks);
            break;
        case 4:
            return false;
    }

    return true;
}

/** ********************************************************************************************************************
 ** Function: InitData
 ** Description: initializes all the different arrays
 ** Parameters: number of spellbooks, reference to input file
 ** Pre-Conditions: file must exist
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

Spellbook* InitData(int numSpellbooks, ifstream& f) {
    Spellbook* spellbookArr = CreateSpellbook(numSpellbooks, f);

    for (int i = 0; i < numSpellbooks; i++) {
        GetSpellbookData(&spellbookArr[i], f);
        spellbookArr[i].sArr = CreateSpells(spellbookArr[i].numSpells);

        for (int j = 0; j < spellbookArr[i].numSpells; j++) {
            GetSpellData(spellbookArr[i].sArr, j, f);
        }
    }
    return spellbookArr;
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

int main(int argc, char* argv[]) {
    ifstream f;
    int numSpellbooks;

    if (argc == 2) {

        string fileName = argv[1];
        f.open(fileName.c_str(), ios::in);

        if (!f) {
            cout << "ERROR: That wasn't a valid filepath";
            return 1;
        }

        f >> numSpellbooks;
        Spellbook* spellbookArr = InitData(numSpellbooks, f);

        GetAvgSuccess(spellbookArr, numSpellbooks);

        bool wantsToSort = true;
        while (wantsToSort) {
            wantsToSort = GetSortMethod(spellbookArr, numSpellbooks);
        }

        DeleteSpellbookData(spellbookArr, numSpellbooks);
    } else {
        cout << "ERROR: Incorrect number of arguments";
        return 1;
    }

    return 0;
}