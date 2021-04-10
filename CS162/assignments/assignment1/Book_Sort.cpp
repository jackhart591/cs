#include <iostream>
#include <fstream>
#include "Book_Sort.h"

using namespace std;

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

Spellbook* CreateSpellbook(int numSpellbooks, ifstream& f) {
    Spellbook* bookArr = new Spellbook[numSpellbooks];

    for(int i = 0; i < numSpellbooks; i++) {
        bookArr[i].sArr = NULL;
    }

    return bookArr;
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
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
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void GetSpellbookData(Spellbook* spellbook, ifstream& f) {
    f >> spellbook->title;
    f >> spellbook->author;
    f >> spellbook->numPages;
    f >> spellbook->edition;
    f >> spellbook->numSpells;
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void Display(bool toScreen, Spellbook* spellbookArr, int numSpellbooks) {
    if (toScreen) {
        for (int i = 0; i < numSpellbooks; i++) {
            cout << "Title: " << spellbookArr[i].title << endl;
            cout << "Author: " << spellbookArr[i].author << endl;
            cout << "Average Success Rate: " << spellbookArr[i].avgSuccess << endl;
            cout << "Number of Pages: " << spellbookArr[i].numPages << endl;
            
            for (int j = 0; j < spellbookArr[i].numSpells; j++) {
                cout << "\t Spell Name: " << spellbookArr[i].sArr[j].name << endl;
                cout << "\t Spell Effect: " << spellbookArr[i].sArr[j].effect << endl;
                cout << "\t Spell Accuracy: " << spellbookArr[i].sArr[j].successRate << endl << endl;
            }
        }
    }
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void Display(bool toScreen, Spell* spells, int numSpells) {
    if (toScreen) {
        for (int i = 0; i < numSpells; i++) {
            cout << spells[i].name << " " << spells[i].effect << " " << spells[i].successRate << endl;
        }
    }
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void SearchForEffect(Spell* spellArr, Spell spell, int& i, string effect) {
    if (spell.effect.compare(effect) == 0) {
        spellArr[i] = spell;
        i++;
    }
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
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
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
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
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
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
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void SortByMethod(string method, Spellbook* spellbookArr, int numSpellbooks) {
    if (method.compare("numPages") == 0) {
        SortByPages(spellbookArr, numSpellbooks);
        Display(true, spellbookArr, numSpellbooks);
    } else if (method.compare("avgSuccess") == 0) {
        SortBySuccess(spellbookArr, numSpellbooks);
        Display(true, spellbookArr, numSpellbooks);
    } else if (method.compare("effect") == 0) {

        int numSpells = 0;

        for (int i = 0; i < numSpellbooks; i++) {
            numSpells += spellbookArr[i].numSpells;
        }

        Spell* spellArr = new Spell[numSpells];

        SortByEffect(spellbookArr, spellArr, numSpellbooks);
        Display(true, spellArr, numSpells);

        delete [] spellArr;
    }
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

Spell* CreateSpells(int numSpells) {
    Spell* spell = new Spell[numSpells];
    return spell;
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void GetSpellData(Spell* spell, int something, ifstream& f) {
    f >> spell->name;
    f >> spell->successRate;
    f >> spell->effect;
}

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void DeleteSpellbookData(Spellbook* spellbookArr, int numSpellbooks) {
    for (int i = 0; i < numSpellbooks; i++) {
        delete [] spellbookArr[i].sArr;
    }

    delete [] spellbookArr;
}