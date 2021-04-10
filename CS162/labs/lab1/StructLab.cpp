#include <iostream>
#include <stdlib.h>

using namespace std;

struct point {
     int mult;
     float div;
};

int GetValidDimension(char* n, bool x) {
    int value;
    bool isValid = false;
    if ((int(n) > 47 && int(n) < 58) || x) {
        value = atoi(n);
    } else if (x) {
        value = 0;
    } else {
        cin >> value;
    }
    do {
        if (cin.fail() || value <= 0) {
            cout << "That wasn't valid, please try again - ";
            cin >> value; 
        } else {
            isValid = true;
        }
    } while (!isValid);

    return value;
}

point** CreatePointArray(int size) {
    point** arr = new point*[size];

    for (int i = 0; i < size; i++) {
        arr[i] = new point[size];
    }

    return arr;
}

void FillArray(point** table, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            table[i][j].mult = (i+1) * (j+1);
            table[i][j].div = (float)(i+1) / (float)(j+1);
        }
    }
}

void PrintArr(point** arr, int size) {
    cout << "Mult Table" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j].mult << "\t";
        }
        cout << endl;
    }

    cout << "Div Table" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j].div << "\t";
        }
        cout << endl;
    }
}

void DeleteArr(point** array, int size) {
    for(int i = 0; i < size; i++) {
        delete [] array[i];
    }
    delete [] array;
}

int main (int argc, char* argv[]) {
    
    int size = GetValidDimension(argv[1], true);

    bool keepPlaying = false;
    do {
        point** table = CreatePointArray(size);
        FillArray(table, size);
        PrintArr(table, size);

        cout << "Would you like to play again? (0 - no, 1 - yes) - ";
        cin >> keepPlaying;
        int newSize = 0;
        if (keepPlaying) {
            cout << "Enter a new dimension: ";
            newSize = GetValidDimension(argv[1], false);
        }
        DeleteArr(table, size);
        size = newSize;
    } while (keepPlaying);

    return 0;
}