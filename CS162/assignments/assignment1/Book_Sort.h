#pragma once

struct Spell {
    std::string name;
    float successRate;
    std::string effect;
};

struct Spellbook {
    std::string title;
    std::string author;
    int numPages;
    int edition;
    float avgSuccess;
    int numSpells;
    Spell* sArr;
};

float GetAvgSuccess(Spellbook*);
Spellbook* CreateSpellbook(int, std::ifstream&);
void GetSpellbookData(Spellbook*, std::ifstream&);
Spell* CreateSpells(int);
void GetSpellData(Spell*, int, std::ifstream&);
void GetAvgSuccess(Spellbook*, int);
void SortByMethod(std::string, Spellbook*, int);
void DeleteSpellbookData(Spellbook*, int);