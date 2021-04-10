#include <iostream>
#include <fstream>
#include "Book_Sort.h"

/**********************************************************************************************************************
 ** Program Filename: Book_Sort.cpp
 ** Author: Jackson Hart
 ** Date: 4/10/2021
 ** Description: Contains all dependencies needed for Book_Sort_Driver.cpp
 ** Input: none
 ** Output: sorted spells/spellbooks
 ** *******************************************************************************************************************/

using namespace std;

/** ********************************************************************************************************************
 ** Function: CreateSpellbook
 ** Description: Creates an array of spellbooks of specified length and then initializes all the spell structs to null
 ** Parameters: number of spellbooks, reference to file
 ** Pre-Conditions: file has to be initialized
 ** Post-Conditions: an empty spellbook array will be created
 ** ********************************************************************************************************************/

Spellbook* CreateSpellbook(int numSpellbooks, ifstream& f) {
    Spellbook* bookArr = new Spellbook[numSpellbooks];

    for(int i = 0; i < numSpellbooks; i++) {
        bookArr[i].sArr = NULL;
    }

    return bookArr;
}

/** ********************************************************************************************************************
 ** Function: GetAvgSuccess
 ** Description: runs through all the spells in all the spellbooks and averages them per book
 ** Parameters: spellbook array, number of spellbooks
 ** Pre-Conditions: spellbooks must be initalized with values from input file
 ** Post-Conditions: spellbooks will have avg success rate values
 ** ********************************************************************************************************************/

void GetAvgSuccess(Spellbook* spellbook, int numSpellbooks) {
    double average;

    for (int i = 0; i < numSpellbooks; i++) {
        average = 0;
        for (int j = 0; j < spellbook[i].numSpells; j++) {
            average += spellbook[i].sArr[j].successRate;
        }
        spellbook[i].avgSuccess = (average / spellbook[i].numSpells);
    }
}

/** ********************************************************************************************************************
 ** Function: GetSpellbookData
 ** Description: feeds spellbook array data from input file
 ** Parameters: spellbook array, file
 ** Pre-Conditions: spellbook array must be declared and initialized
 ** Post-Conditions: spellbook array will be populated with given data
 ** ********************************************************************************************************************/

void GetSpellbookData(Spellbook* spellbook, ifstream& f) {
    f >> spellbook->title;
    f >> spellbook->author;
    f >> spellbook->numPages;
    f >> spellbook->edition;
    f >> spellbook->numSpells;
}

/** ********************************************************************************************************************
 ** Function: DisplaySuccess
 ** Description: displays spellbook title and avg success stat to either screen or given file 
 ** Parameters: whether to screen or file, spellbook array, number of spellbooks, file name for outputting
 ** Pre-Conditions: spellbook array must be initialized and populated
 ** Post-Conditions: spellbook avg success will have been displayed in some way
 ** ********************************************************************************************************************/

void DisplaySuccess(bool toScreen, Spellbook* spellbookArr, int numSpellbooks, string outFileName) {
    if (toScreen) {
        for (int i = 0; i < numSpellbooks; i++) {
            cout << spellbookArr[i].title << " " << spellbookArr[i].avgSuccess << endl;
        }
    } else {
        ofstream outfile(outFileName.c_str(), ios::app);
        for (int i = 0; i < numSpellbooks; i++) {
            outfile << spellbookArr[i].title << " " << spellbookArr[i].avgSuccess << endl;
        }
        outfile << endl << endl;
        outfile.close(); 
    }
}

/** ********************************************************************************************************************
 ** Function: DisplayPages
 ** Description: displays spellbook title and number of pages to either screen or given file 
 ** Parameters: whether to screen or file, spellbook array, number of spellbooks, file name for outputting
 ** Pre-Conditions: spellbook array must be initialized and populated
 ** Post-Conditions: spellbook pages will have been displayed in some way
 ** ********************************************************************************************************************/

void DisplayPages(bool toScreen, Spellbook* spellbookArr, int numSpellbooks, string outFileName) {
    if (toScreen) {
        for (int i = 0; i < numSpellbooks; i++) {
            cout << spellbookArr[i].title << " " << spellbookArr[i].numPages << endl;
        }
    } else {
        ofstream outfile(outFileName.c_str(), ios::app);
        for (int i = 0; i < numSpellbooks; i++) {
            outfile << spellbookArr[i].title << " " << spellbookArr[i].numPages << endl;
        }
        outfile << endl << endl;
        outfile.close(); 
    }
}

/** ********************************************************************************************************************
 ** Function: DisplaySpells
 ** Description: displays spells and their effects to either screen or given output file
 ** Parameters: whether to screen or file, spell array, number of spells, file name for outputting
 ** Pre-Conditions: spellbook array must be initialized and populated
 ** Post-Conditions: spells will have been displayed in some way
 ** ********************************************************************************************************************/

void DisplaySpells(bool toScreen, Spell* spells, int numSpells, string outFileName) {
    if (toScreen) {
        for (int i = 0; i < numSpells; i++) {
            cout << spells[i].name << " " << spells[i].effect << " " << spells[i].successRate << endl;
        }
    } else {
        ofstream outfile(outFileName.c_str(), ios::app);
        for (int i = 0; i < numSpells; i++) {
            outfile << spells[i].name << " " << spells[i].effect << " " << spells[i].successRate << endl;
        }
        outfile << endl << endl;
        outfile.close();
    }
}

/** ********************************************************************************************************************
 ** Function: SearchForEffect
 ** Description: compares spell effect to given effect and puts it into spell array if that is true
 ** Parameters: spell array, spell to compare, what iteration we're on, the effect
 ** Pre-Conditions: spell array must be initialized
 ** Post-Conditions: spell array will be slightly more populated
 ** ********************************************************************************************************************/

void SearchForEffect(Spell* spellArr, Spell spell, int& i, string effect) {
    if (spell.effect.compare(effect) == 0) {
        spellArr[i] = spell;
        i++;
    }
}

/** ********************************************************************************************************************
 ** Function: SortByPages
 ** Description: sorts the spellbook array but number of pages
 ** Parameters: spellbook array, number of spellbooks
 ** Pre-Conditions: spellbook array must be populated
 ** Post-Conditions: spellbook array will be sorted by number of pages
 ** ********************************************************************************************************************/

void SortByPages(Spellbook* spellbookArr, int numSpellbooks) {
    for (int i = 0; i < numSpellbooks-1; i++) {
        for (int j = 0; j < numSpellbooks-i-1; j++) {
            if (spellbookArr[j].numPages < spellbookArr[j+1].numPages) {
                Spellbook temp = spellbookArr[j];
                spellbookArr[j] = spellbookArr[j+1];
                spellbookArr[j+1] = temp;
            }
        }
    }
}

/** ********************************************************************************************************************
 ** Function: SortBySuccess
 ** Description: sorts the spellbook array but average success
 ** Parameters: spellbook array, number of spellbooks
 ** Pre-Conditions: spellbook array must be populated
 ** Post-Conditions: spellbook array will be sorted by average success
 ** ********************************************************************************************************************/

void SortBySuccess(Spellbook* spellbookArr, int numSpellbooks) {
    for (int i = 0; i < numSpellbooks-1; i++) {
        for (int j = 0; j < numSpellbooks-i-1; j++) {
            if (spellbookArr[j].avgSuccess < spellbookArr[j+1].avgSuccess) {
                Spellbook temp = spellbookArr[j];
                spellbookArr[j] = spellbookArr[j+1];
                spellbookArr[j+1] = temp;
            }
        }
    }
}

/** ********************************************************************************************************************
 ** Function: SortByEffect
 ** Description: sorts the spell array but effect
 ** Parameters: spellbook array, spell array, number of spellbooks
 ** Pre-Conditions: spellbook array must be populated and spell array must be initialized
 ** Post-Conditions: spell array will be populated with spells grouped by effect
 ** ********************************************************************************************************************/

void SortByEffect(Spellbook* spellbookArr, Spell* spellArr, int numSpellbooks) {
    int it = 0;

    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < numSpellbooks; j++) {
            for (int k = 0; k < spellbookArr[j].numSpells; k++) {
                switch(i) {
                    case 0:
                        SearchForEffect(spellArr, spellbookArr[j].sArr[k], it, "bubble");
                        break;
                    case 1:
                        SearchForEffect(spellArr, spellbookArr[j].sArr[k], it, "memory_loss");
                        break;
                    case 2:
                        SearchForEffect(spellArr, spellbookArr[j].sArr[k], it, "fire");
                        break;
                    case 3:
                        SearchForEffect(spellArr, spellbookArr[j].sArr[k], it, "poison");
                        break;
                    case 4:
                        SearchForEffect(spellArr, spellbookArr[j].sArr[k], it, "death");
                        break;
                }
            }
        }
    }
}

/** ********************************************************************************************************************
 ** Function: GetDisplayMethod
 ** Description: prompts user for which type of display method they'd like to use
 ** Parameters: reference to the outfile's name
 ** Pre-Conditions: none
 ** Post-Conditions: program knows whether user wants to print to screen or text file and the name of that text file
 ** ********************************************************************************************************************/

bool GetDisplayMethod(string& outfileName) {
    cout << "Would you like to <1> Print to screen or <2> Print to text file? - ";

    int print;
    cin >> print;

    while (cin.fail() || (print != 1 && print != 2)) {
        cout << endl << "That wasn't a valid option, please try again - ";
        cin >> print;
    }

    if (print == 1) {
        outfileName = "******";
        return true;
    } else if (print == 2) {
        cout << "What is the name of the file you would like to print to? - ";
        cin.ignore();
        getline(cin, outfileName);
        return false;
    }
}

/** ********************************************************************************************************************
 ** Function: SortByMethod
 ** Description: begins process of sorting by given method 
 ** Parameters: method to sort by (can be either numPages, avgSuccess, or effect), spellbook array, and number of spell-
                -books
 ** Pre-Conditions: spellbook array must be populated and user must have been prompted for sort method
 ** Post-Conditions: spellbook array will be sorted by either number of pages or average success or spells will have been
                     grouped by effect
 ** ********************************************************************************************************************/

void SortByMethod(string method, Spellbook* spellbookArr, int numSpellbooks) {
    string outfileName;
    bool print = GetDisplayMethod(outfileName);
    if (method.compare("numPages") == 0) {
        SortByPages(spellbookArr, numSpellbooks);
        DisplayPages(print, spellbookArr, numSpellbooks, outfileName);
    } else if (method.compare("avgSuccess") == 0) {
        SortBySuccess(spellbookArr, numSpellbooks);
        DisplaySuccess(print, spellbookArr, numSpellbooks, outfileName);
    } else if (method.compare("effect") == 0) {

        int numSpells = 0;

        for (int i = 0; i < numSpellbooks; i++) {
            numSpells += spellbookArr[i].numSpells;
        }

        Spell* spellArr = CreateSpells(numSpells);

        SortByEffect(spellbookArr, spellArr, numSpellbooks);
        DisplaySpells(print, spellArr, numSpells, outfileName);

        delete [] spellArr;
    }
}

/** ********************************************************************************************************************
 ** Function: CreateSpells
 ** Description: initializes spell array of given length
 ** Parameters: number of spells
 ** Pre-Conditions: none
 ** Post-Conditions: spell array will have been initialized
 ** ********************************************************************************************************************/

Spell* CreateSpells(int numSpells) {
    Spell* spell = new Spell[numSpells];
    return spell;
}

/** ********************************************************************************************************************
 ** Function: GetSpellData
 ** Description: populates spell array with input from file
 ** Parameters: spell array, iteration, reference to input file
 ** Pre-Conditions: spell array must have been initialized using CreateSpells()
 ** Post-Conditions: spell array will be populated with spells
 ** ********************************************************************************************************************/

void GetSpellData(Spell* spell, int i, ifstream& f) {
    f >> spell[i].name;
    f >> spell[i].successRate;
    f >> spell[i].effect;
}

/** ********************************************************************************************************************
 ** Function: DeleteSpellbookData
 ** Description: deletes all the spell arrays followed by the spellbook array
 ** Parameters: spellbook array, number of spellbooks
 ** Pre-Conditions: spellbook array and respective spell arrays must've been initialized
 ** Post-Conditions: spellbook array and respective spell arrays will have been deleted
 ** ********************************************************************************************************************/

void DeleteSpellbookData(Spellbook* spellbookArr, int numSpellbooks) {
    for (int i = 0; i < numSpellbooks; i++) {
        delete [] spellbookArr[i].sArr;
    }

    delete [] spellbookArr;
}