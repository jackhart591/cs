#include <iostream>
#include <stdlib.h>

using namespace std;

/**********************************************************************************************************************
 ** Program Filename: Connect_Four.cpp
 ** Author: Jackson Hart
 ** Date: 3/14/2021
 ** Description: Allows two users to play connect four together or 1 player play with an AI
 ** Input: number of players, size of board, and what they'd like to play
 ** Output: game board and who won
 ** *******************************************************************************************************************/

struct Board {
    int** array;
    int numOfColumns;
    int numOfRows;
};

void EnterStuff(Board& board, int& numOfPlayers);
int InputHandler();
bool InputHandler(bool x);
bool InputHandler(bool x, bool y);
bool PlayGame(Board& board, int numOfPlayers);
void ArgErrorHandler(Board& board, int& numOfPlayers);
void DrawBoard(Board board);
void PlayerQuery(Board board, int currentPlayer);
bool CheckWin(Board board, int currentPlayer);
void AIPlay (Board board, int currentPlayer);

/** ********************************************************************************************************************
 ** Function: main
 ** Description: runs program
 ** Parameters: number of args, array of args
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

int main(int argc, char* argv[]) {

    Board board;
    int numOfPlayers;

    numOfPlayers = 0;
    board.numOfColumns = 0;
    board.numOfRows = 0;

    // error trapping args
    if (argc != 4) {
        EnterStuff(board, numOfPlayers);
    } else {
        numOfPlayers = atoi(argv[1]);
        board.numOfColumns = atoi(argv[2]);
        board.numOfRows = atoi(argv[3]);
        ArgErrorHandler(board, numOfPlayers);
    }
    
    srand(time(NULL));

    board.array = new int*[board.numOfColumns];

    // runs game
    bool playAgain = false;
    do {
        playAgain = PlayGame(board, numOfPlayers);
    } while (playAgain);

    for (int i = 0; i < board.numOfColumns; i++) {
        delete [] board.array[i];
        board.array[i] = NULL;
    }

    delete [] board.array;
    board.array = NULL;

    return 0;
}

/** ********************************************************************************************************************
 ** Function: DudeImSoDone
 ** Description: Runs correct sequence of functions based on number of players
 ** Parameters: whether this is two player or one, and reference to the board
 ** Pre-Conditions: board is initialized
 ** Post-Conditions: game will have been played
 ** ********************************************************************************************************************/

void DudeImSoDone(bool x, Board& board) {
    int currentPlayer = 1;
    bool hasWon = false;
    int playerNum;

    if (!x) { // With AI?
        currentPlayer = 1;
        cout << "Would you like to play as player (1) or player (2) - ";
        playerNum = InputHandler(true, false);
    }

    do {
        DrawBoard(board);
        if (x || currentPlayer == playerNum) {
            PlayerQuery(board, currentPlayer);
        } else if (!x && currentPlayer != playerNum) {
            AIPlay(board, currentPlayer);
        }

        if (CheckWin(board, currentPlayer)) {
            DrawBoard(board);
            cout << "Player " << currentPlayer << " Won!!" << endl;
            hasWon = true;
        } else {currentPlayer = (currentPlayer == 1) ? 2 : 1;}

    } while (!hasWon);
}

/** ********************************************************************************************************************
 ** Function: PlayGame
 ** Description: Initializes board, and then runs DudeImSoDone
 ** Parameters: reference to board and number of players
 ** Pre-Conditions: none
 ** Post-Conditions: game will be either restarted or over
 ** ********************************************************************************************************************/

bool PlayGame(Board& board, int numOfPlayers) {

    // Inits board
    for (int i = 0; i < board.numOfColumns; i++) {
        board.array[i] = new int[board.numOfRows];
        for (int j = 0; j < board.numOfRows; j++) {
            board.array[i][j] = 0;
        }
    }

    if (numOfPlayers == 2) {
        DudeImSoDone(true, board);
    } else {
        DudeImSoDone(false, board);
    }

    cout << "Would you like to play again? (1 - yes, 0 - no) - ";
    return InputHandler(true);
}

/** ********************************************************************************************************************
 ** Function: EnterStuff
 ** Description: Has user reenter args if there wasn't the right amount or weren't right type
 ** Parameters: reference to board and number of players
 ** Pre-Conditions: args weren't valid
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void EnterStuff(Board& board, int& numOfPlayers) {
    cout << "Please enter number of players - ";
    numOfPlayers = InputHandler();
    cout << endl << "Please enter number of columns - ";
    board.numOfColumns = InputHandler();
    cout << endl << "Please enter number of rows - ";
    board.numOfRows = InputHandler();
    ArgErrorHandler(board, numOfPlayers);
}

/** ********************************************************************************************************************
 ** Function: ArgErrorHandler
 ** Description: Makes sure all the arg values make sense
 ** Parameters: reference to board and number of players
 ** Pre-Conditions: args weren't right numbers
 ** Post-Conditions: args will be the right numbers
 ** ********************************************************************************************************************/

void ArgErrorHandler(Board& board, int& numOfPlayers) {
    bool invalid = false;

    if ((board.numOfRows > 20 || board.numOfColumns > 20)) {
        cout << "ERROR: board is too big" << endl;
        cout << "board can't be larger than 20x20" << endl;
        invalid = true;
    } else if (board.numOfRows < 4 || board.numOfColumns < 4) {
        cout << "ERROR: board is unwinnable" << endl;
        cout << "board can't be smaller than 4x4" << endl;
        invalid = true;
    } else if (numOfPlayers <= 0 || numOfPlayers > 2) {
        cout << "ERROR: Invalid number of players" << endl;
        cout << "Number of players must between 1 and 2" << endl;
        invalid = true;
    }

    if (invalid) {
        EnterStuff(board, numOfPlayers);
    }
}

/** ********************************************************************************************************************
 ** Function: InputHandler()
 ** Description: Makes sure int input is valid
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid int input
 ** ********************************************************************************************************************/

int InputHandler() {
    int input;
    cin >> input;

    if (cin.fail()) {
        do {
            cin.clear();
            cin.ignore(256, '\n');
            cout << endl << "That wasn't a valid input, try again - ";
            cin >> input;
        } while (cin.fail());
    }
    return input;
}

/** ********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Makes sure int input is valid
 ** Parameters: board
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid int input
 ** ********************************************************************************************************************/

int InputHandler(Board board) {
    int input;
    cin >> input;

    if (cin.fail()) {
        do {
            cin.clear();
            cin.ignore(256, '\n');
            cout << endl << "That wasn't a valid input, try again - ";
            cin >> input;
        } while (cin.fail());
    }

    input--;

    if (input < 0 || input >= board.numOfColumns) {
        cout << endl << "That wasn't a valid option, try again - ";
        input = InputHandler(board);
    } else if (board.array[input][0] == 1) {
        cout << "This column's full!, try again -";
        input = InputHandler(board);
    } else return (input);
}
/** ********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Makes sure int input is valid
 ** Parameters: arbitrary values to distinguish this function
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid boolean input
 ** ********************************************************************************************************************/

bool InputHandler(bool x) {
    int input;
    cin >> input;

    if (cin.fail()) {
        do {
            cin.clear();
            cin.ignore(256, '\n');
            cout << endl << "That wasn't a valid input, try again - ";
            cin >> input;
        } while (cin.fail());
    }
    
    if (input != 1 && input != 0) {
        cout << "That wasn't a valid answer, try again - ";
        InputHandler(true);
    }
}

/** ********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Makes sure int input is valid
 ** Parameters: arbitrary values to distinguish this function
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid boolean input
 ** ********************************************************************************************************************/

bool InputHandler (bool x, bool y) {
    int input;
    cin >> input;

    if (cin.fail()) {
        do {
            cin.clear();
            cin.ignore(256, '\n');
            cout << endl << "That wasn't a valid input, try again - ";
            cin >> input;
        } while (cin.fail());
    }
    
    if (input != 2 && input != 1) {
        cout << "That wasn't a valid answer, try again - ";
        InputHandler(true);
    }
}

/** ********************************************************************************************************************
 ** Function: DrawBoard
 ** Description: Draws the board with all the correct flairs
 ** Parameters: board
 ** Pre-Conditions: none
 ** Post-Conditions: board will be printed
 ** ********************************************************************************************************************/

void DrawBoard(Board board) {

    system("clear");
    for (int i = 1; i <= board.numOfColumns; i++) {
        cout << "|\033[0m " << i << " "; 
    }

    cout << endl;

    for (int i = 0; i < board.numOfRows; i++) {
        for (int j = 0; j < board.numOfColumns; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                cout << "|\033[30;47m " << board.array[j][i] << " "; 
            } else if (i % 2 == 1 && j % 2 == 1) {
                cout << "|\033[30;47m " << board.array[j][i] << " ";
            } else {
                cout << "|\033[0m " << board.array[j][i] << " ";
            }
            cout << "\033[0m";
        }
        cout << endl;
    }
}

/** ********************************************************************************************************************
 ** Function: DropPiece
 ** Description: Finds lowest possible y value for given x value
 ** Parameters: board, x value, and current player (1 or 2)
 ** Pre-Conditions: player has been prompted for which column
 ** Post-Conditions: array will be updated with a new piece
 ** ********************************************************************************************************************/

void DropPiece(Board board, int columnChoice, int currentPlayer) {
    for (int i = 0; i < board.numOfRows; i++) {
        if (i == board.numOfRows-1 || board.array[columnChoice][i+1] == 1 || board.array[columnChoice][i+1] == 2) {
            board.array[columnChoice][i] = currentPlayer;
            break;
        }
    }
}

/** ********************************************************************************************************************
 ** Function: PlayerQuery
 ** Description: Asks which column player would like to play
 ** Parameters: board and current player
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

void PlayerQuery(Board board, int currentPlayer) {
    cout << "Player " << currentPlayer << ", Which column would you like to play? - ";
    int columnChoice = InputHandler(board);
    DropPiece(board, columnChoice, currentPlayer);
}

/** ********************************************************************************************************************
 ** Function: isMaxMin
 ** Description: Checks to see if given x and y values are within the bounds
 ** Parameters: board, x, and y
 ** Pre-Conditions: none
 ** Post-Conditions: returns a boolean on whether it's outside or not
 ** ********************************************************************************************************************/

bool isMaxMin(Board board, int i, int j) {
    if (i >= board.numOfColumns || i < 0) {return true;}
    else if (j >= board.numOfRows || j < 0) {return true;} 
    else {return false;}
}

/** ********************************************************************************************************************
 ** Function: CheckWinAtPosition
 ** Description: Recursively checks whether there's a win at a given position in given direction
 ** Parameters: board, x, y, win iterable, direction, and the current player
 ** Pre-Conditions: at least one piece on board
 ** Post-Conditions: returns boolean of whether there's a win or not
 ** ********************************************************************************************************************/

bool CheckWinAtPosition(Board board, int i, int j, int k, char direc, int currentPlayer) {
    if (k < 3) {
        if (direc == 'T' && !isMaxMin(board, i-1, j-1) && board.array[i-1][j-1] == currentPlayer) { // top left corner
            CheckWinAtPosition(board, i-1, j-1, (k+1), direc, currentPlayer);
        } else if (direc == 'U' && !isMaxMin(board, i, j-1) && board.array[i][j-1] == currentPlayer) { // top middle
            CheckWinAtPosition(board, i, j-1, (k+1), direc, currentPlayer);
        } else if (direc == 'O' && !isMaxMin(board, i+1, j-1) && board.array[i+1][j-1] == currentPlayer) { // top right corner
            CheckWinAtPosition(board, i+1, j-1, (k+1), direc, currentPlayer);
        } else if (direc == 'R' && !isMaxMin(board, i+1, j) && board.array[i+1][j] == currentPlayer) { // right middle
            CheckWinAtPosition(board, i+1, j, (k+1), direc, currentPlayer);
        } else if (direc == 'K' && !isMaxMin(board, i+1, j+1) && board.array[i+1][j+1] == currentPlayer) { // bottom right
            CheckWinAtPosition(board, i+1, j+1, (k+1), direc, currentPlayer);
        } else if (direc == 'D' && !isMaxMin(board, i, j+1) && board.array[i][j+1] == currentPlayer) { // bottom middle
            CheckWinAtPosition(board, i, j+1, (k+1), direc, currentPlayer);
        } else if (direc == 'J' && !isMaxMin(board, i-1, j+1) && board.array[i-1][j+1] == currentPlayer) { // bottom left corner
            CheckWinAtPosition(board, i-1, j+1, (k+1), direc, currentPlayer);
        } else if (direc == 'L' && !isMaxMin(board, i-1, j+1) && board.array[i-1][j] == currentPlayer) { // left middle
            CheckWinAtPosition(board, i-1, j, (k+1), direc, currentPlayer);
        } else {return false;}
    } else {return true;}
}

/** ********************************************************************************************************************
 ** Function: CheckWinAtPosition
 ** Description: Recursively checks whether there's a number in a row at a given position in a given direction 
 ** Parameters: board, reference to x value, y, win iterable, number in a row we're looking for, direction, and current
 **             player
 ** Pre-Conditions: none
 ** Post-Conditions: returns whether there's a number in a row or not
 ** ********************************************************************************************************************/

bool CheckWinAtPosition(Board board, int& i, int j, int k, int kMax, char direc, int currentPlayer) {
    if (k < kMax) {
        if (direc == 'T' && !isMaxMin(board, i-1, j-1) && board.array[i-1][j-1] == currentPlayer) { // top left corner
            int p = i-1;
            CheckWinAtPosition(board, p, j-1, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'U' && !isMaxMin(board, i, j-1) && board.array[i][j-1] == currentPlayer) { // top middle
            CheckWinAtPosition(board, i, j-1, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'O' && !isMaxMin(board, i+1, j-1) && board.array[i+1][j-1] == currentPlayer) { // top right corner
            int p = i+1;
            CheckWinAtPosition(board, p, j-1, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'R' && !isMaxMin(board, i+1, j) && board.array[i+1][j] == currentPlayer) { // right middle
            int p = i+1;
            CheckWinAtPosition(board, p, j, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'K' && !isMaxMin(board, i+1, j+1) && board.array[i+1][j+1] == currentPlayer) { // bottom right
            int p = i+1;
            CheckWinAtPosition(board, p, j+1, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'D' && !isMaxMin(board, i, j+1) && board.array[i][j+1] == currentPlayer) { // bottom middle
            CheckWinAtPosition(board, i, j+1, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'J' && !isMaxMin(board, i-1, j+1) && board.array[i-1][j+1] == currentPlayer) { // bottom left corner
            int p = i-1;
            CheckWinAtPosition(board, p, j+1, (k+1), kMax, direc, currentPlayer);
        } else if (direc == 'L' && !isMaxMin(board, i-1, j+1) && board.array[i-1][j] == currentPlayer) { // left middle
            int p = i-1;
            CheckWinAtPosition(board, p, j, (k+1), kMax, direc, currentPlayer);
        } else {return false;}
    } else {return true;}
}

/** ********************************************************************************************************************
 ** Function: CheckWin
 ** Description: Calls CheckWinAtPosition() in correct position and direction
 ** Parameters: board and current player
 ** Pre-Conditions: none
 ** Post-Conditions: returns whether there's a win or not
 ** ********************************************************************************************************************/

bool CheckWin(Board board, int currentPlayer) {

    bool win = false;

    for (int i = 0; i < board.numOfRows; i++) {
        for (int j = 0; j < board.numOfColumns; j++) {
            for (int k = 0; k < 8; k++) {
                if (board.array[j][i] == currentPlayer) {
                    switch (k) {
                        case 0: win = CheckWinAtPosition(board, j, i, 0, 'T', currentPlayer); break;
                        case 1: win = CheckWinAtPosition(board, j, i, 0, 'U', currentPlayer); break;
                        case 2: win = CheckWinAtPosition(board, j, i, 0, 'O', currentPlayer); break;
                        case 3: win = CheckWinAtPosition(board, j, i, 0, 'R', currentPlayer); break;
                        case 4: win = CheckWinAtPosition(board, j, i, 0, 'K', currentPlayer); break;
                        case 5: win = CheckWinAtPosition(board, j, i, 0, 'D', currentPlayer); break;
                        case 6: win = CheckWinAtPosition(board, j, i, 0, 'J', currentPlayer); break;
                        case 7: win = CheckWinAtPosition(board, j, i, 0, 'L', currentPlayer); break;
                    }
                }
                if (win) {break;}
            }
            if (win) {break;}
        }
        if (win) {break;}
    }
    return win;
}

/** ********************************************************************************************************************
 ** Function: CheckWin
 ** Description: Calls correct functions to check for three in a row
 ** Parameters: board, currentPlayer, the amount in a row to check for, and reference to that column, this is over 20
 **             20 lines because I couldn't figure out how to call these functions in a way that was shorter
 ** Pre-Conditions: none
 ** Post-Conditions: returns whether there's a certain number in a row
 ** ********************************************************************************************************************/

bool CheckWin(Board board, int currentPlayer, int winVal, int& p) {

    bool win = false;

    for (int i = 0; i < board.numOfRows; i++) {
        if (win) {break;}
        for (int j = 0; j < board.numOfColumns; j++) {
            if (win) {break;}
            for (int k = 0; k < 8; k++) {
                if (win) {break;}
                if (board.array[j][i] == currentPlayer) {
                    switch (k) {
                        case 0:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'T', currentPlayer);
                            if (!isMaxMin(board, (p-1), (i-1)) && board.array[p-1][i] != 0) {p -= 3;}
                            else {win = false;}
                            break;
                        case 1:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'U', currentPlayer);
                            if (isMaxMin(board, p, (i+1))) {win = false;}
                            break;
                        case 2:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'O', currentPlayer);
                            if (!isMaxMin(board, (p+1), (i-1)) && board.array[p+1][i] != 0) {p += 3;}
                            else {win = false;}
                            break;
                        case 3:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'R', currentPlayer);
                            if (!isMaxMin(board, (p+1), i)) {p += 3;}
                            else {win = false;}
                            break;
                        case 4:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'K', currentPlayer);
                            if (!isMaxMin(board, (p+1), (i+1))) {p += 3;}
                            else {win = false;}
                            break;
                        case 5:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'D', currentPlayer);
                            break;
                        case 6:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'J', currentPlayer);
                            if (!isMaxMin(board, (p-1), i)) {p -= 3;}
                            else {win = false;}
                            break;
                        case 7:
                            p = j;
                            win = CheckWinAtPosition(board, p, i, 0, winVal, 'L', currentPlayer);
                            if (!isMaxMin(board, (p-1), i)) {p -= 3;}
                            else {win = false;}
                            break;
                    }
                }
            }
        }
    }
    return win;
}

/** ********************************************************************************************************************
 ** Function: AIPlay
 ** Description: Has AI play a piece if there's a way for it to win, block player if they can win, or place a piece
 **              randomly
 ** Parameters: arbitrary values to distinguish this function
 ** Pre-Conditions: none
 ** Post-Conditions: returns a valid boolean input
 ** ********************************************************************************************************************/

void AIPlay(Board board, int currentPlayer) {
    int play = 0;
    int playerNum = (currentPlayer == 2) ? 1 : 2;

    if (!CheckWin(board, currentPlayer, 2, play) || board.array[play][0] != 0) {
        if (!CheckWin(board, playerNum, 2, play) || board.array[play][0] != 0) {
            play = rand() % board.numOfColumns;
        }
    }

    DropPiece(board, play, currentPlayer);

}