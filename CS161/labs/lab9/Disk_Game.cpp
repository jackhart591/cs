#include <iostream>
#include <stdlib.h>

using namespace std;

void PrintArray(int** arr) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------" << endl;
}

void Towers(int numOfDisks, int** board, int fromCol, int toCol, int spare) {
    if (numOfDisks >= 1) {
        Towers(numOfDisks-1, board, fromCol, spare, toCol);

        for (int i = 0; i < 3; i++) {
            if (board[i][fromCol] == numOfDisks) {
                board[i][fromCol] = 0;
            }
        }

        for (int i = 3-1; i >= 0; i--) {
            if(board[i][toCol] == 0) {
                board[i][toCol] = numOfDisks;
                break;
            }
        }

        PrintArray(board);

        Towers(numOfDisks-1, board, spare, toCol, fromCol);

    }
}

int main(int argc, char* argv[]) {

    int numOfDisks = atoi(argv[1]);

    int** board = new int*[numOfDisks];

    // init board
    for (int i = 0; i < numOfDisks; i++) {
        board[i] = new int[3];
        for(int j = 0; j < 3; j++) {
            if (j == 0) {
                board[i][j] = i+1;
            } else {
                board[i][j] = 0;
            }
        }
    }

    PrintArray(board);

    Towers(3, board, 0, 1, 2);
    
    for (int i = 0; i < numOfDisks; i++) {
        delete [] board[i];
    }

    delete [] board;

    return 0;
}