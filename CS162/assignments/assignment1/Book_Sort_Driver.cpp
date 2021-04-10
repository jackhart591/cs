#include <iostream>
#include <string>
#include <fstream>
#include "Book_Sort.h"

using namespace std;

int main() {
    ifstream f;
    int numSpellbooks;

    f.open("test.txt", ios::in);
    f >> numSpellbooks;

    Spellbook* spellbookArr = CreateSpellbook(numSpellbooks, f);

    for (int i = 0; i < numSpellbooks; i++) {
        GetSpellbookData(&spellbookArr[i], f);
        spellbookArr[i].sArr = CreateSpells(spellbookArr[i].numSpells);

        for (int j = 0; j < spellbookArr[i].numSpells; j++) {
            GetSpellData(&(spellbookArr[i].sArr[j]), 5, f);
        }
    }

    GetAvgSuccess(spellbookArr, numSpellbooks);
    SortByMethod("effect", spellbookArr, numSpellbooks);

    DeleteSpellbookData(spellbookArr, numSpellbooks);

    return 0;
}