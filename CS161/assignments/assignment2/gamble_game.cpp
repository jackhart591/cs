#include <iostream>
#include <string>
#include <cstdlib>

/**********************************************************************************************************************
 ** Program Filename: text_adventure.cpp
 ** Author: Jackson Hart
 ** Date: 1/31/2021
 ** Description: Program determines how many players are playing, what their starting balance is, and then has them roll
 **              a die, if it's under 21 it asks them if they'd like to roll again until either they say no or it equals
 **              21 or above. After all players and the dealer have gotten their score, the program determines who out
 **              the players beat the dealer and gives or takes their bet respectively. 
 ** Input: any number between 1 and 4, 0, 1, and any number over 0
 ** Output: Who won their bets, what their balance is, and any text that helps get to that point (i.e. "would you like
 **         to roll again?")
 ** *******************************************************************************************************************/

using namespace std;

/**********************************************************************************************************************
 ** Class: Player
 ** Description: Stores each player's balance, bet score
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ** ********************************************************************************************************************/

class player {

  public:
  int balance;
  int bet;
  int score;

};

/**********************************************************************************************************************
 ** Function: playerRoll
 ** Description: Runs one individual player through the scoring loop until either their score is greater or equal to 21
 **              or they're satisfied
 ** Parameters: i (the current player index), player bet, the player array
 ** Pre-Conditions: Bets must have been initialized
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void playerRoll(int i, int bet, player playerArray[]) {

  int score = 0; 
  
  // Loop for rolling  
  bool satisfied = false;    
  do {
      
    score += (rand() % 11) + 1;
    
    cout << "Your score comes out to: " << score << endl;
    
    if (score > 21) {
    
      cout << "You over rolled and lost your bet, sorry!" << endl << endl;
      score = -1; 
      satisfied = true;
    
    } else if (score == 21) {
    
      satisfied = true;
    
    } else {
    
      cout << "Would you like to roll again? (1 - no, 0 - yes) - ";
      
      // Determine if this input is good    
      bool isValid = false;
      do {
          
        int ans;
        cin >> ans;
        cout << endl;
              
        if (ans != 1 && ans != 0) {
              
          cout << "That wasn't a proper answer, try again - ";
              
        } else {
              
          satisfied = (bool)ans;
          isValid = true;
              
        } 
          
      } while (!isValid);
        
    } 
    
  } while (!satisfied);
  
  playerArray[i].score = score;
  cout << endl;

}

/**********************************************************************************************************************
 ** Function: dealerRoll
 ** Description: Determines the dealer's score by having him run through the same random roll until he gets between 18
 **              or 21 including those numbers
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

int dealerRoll() {

  int score = 0;
  int fakeScore = 0;
  
  bool satisfied = false;
  do {
  
    score += (rand() % 11) + 1;
    fakeScore = score;
    
    if (score >= 18 && score <= 21) {
    
      satisfied = true; 
    
    } else if (score > 21) {
    
      score = 0;
      satisfied = true;
    
    }
  
  } while (!satisfied);
  
  cout << "Dealer gets a score of " << fakeScore << endl;
  
  return score;

}

/**********************************************************************************************************************
 ** Function: gameCalc
 ** Description: Looks at all the scores and determines the player's new balances based on whether they won or not
 ** Parameters: dealer's score, number of players, array of players
 ** Pre-Conditions: All players and dealer have gotten their scores
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void gameCalc(int dealerScore, int numOfPlayers, player playerArray[]) {

  // Loop through all players
  for (int i = 0; i < numOfPlayers; i++) {
    
    // Did the player win?
    if (dealerScore < playerArray[i].score) {
    
      cout << "Player " << i + 1 << " won against the dealer" << endl;
      playerArray[i].balance += playerArray[i].bet;
      cout << "Making their new balance " << playerArray[i].balance << endl << endl;
    
    // Did the player tie with the dealer?
    } else if (dealerScore == playerArray[i].score) {
      
      cout << "Player " << i + 1 << " got the same score as the dealer, meaning nothing happens!" << endl << endl;
    
    // Did the player lose?
    } else if (dealerScore > playerArray[i].score) {
    
      cout << "Player " << i + 1 << " lost to the dealer" << endl;
      playerArray[i].balance -= playerArray[i].bet;
      cout << "Making their new balance " << playerArray[i].balance << endl << endl;
    
    }
  
  }

}

/**********************************************************************************************************************
 ** Function: gamePlay
 ** Description: Initializes bets for each player and then runs a loop of playerRoll for each player, then runs the
 **              dealerScore function, and then the gameCalc function
 ** Parameters: number of players, player array
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void gamePlay(int numOfPlayers, player playerArray[]) {

  int dealerScore = 0;
  
  // One extra for the dealer at the end
  for (int i = 0; i < numOfPlayers + 1; i++) {
  
    // Players bets
    if (i < numOfPlayers) {
      
      //makes sure bet is valid
      if (playerArray[i].balance > 0) {
      
        int bet = 0;
        cout << "Player " << i + 1 << ", what are you betting? - ";
        cin >> bet;
        
        if (bet <= 0) {
        
          bool isValid = false;
          do {
          
            cout << "That wasn't valid, try again - ";
            cin >> bet;
            
            if (bet > 0) {
            
              isValid = true;
            
            }
          
          } while (!isValid);
        
        }
            
        if (bet > playerArray[i].balance) {
            
          bool isValid = false;
        	
       	  while (!isValid) {
            
       	    cout << "That bet was larger than your balance of " << playerArray[i].balance << endl;
         	  cout << "Please try again - ";
         	  cin >> bet;
            
            if (bet <= playerArray[i].balance) {
            
              isValid = true; 
            
         	  }
          
       	  } 		        
            
        }
        
        // if bet is valid, sets that players bet to that value then determines their score
        playerArray[i].bet = bet;
        playerRoll(i, bet, playerArray);
        
      }
    
    // once all players are done, determine dealer's score
    } else {
      
      dealerScore = dealerRoll();
    
    }
  
  }
  
  // now that all scores are determined, figure out who won
  gameCalc(dealerScore, numOfPlayers, playerArray);
  
}

/**********************************************************************************************************************
 ** Function: main
 ** Description: Determines amount of players, makes sure that was a valid answer, then determines starting balance and
 **              whether that was valid, and then runs gameplay function. After that is done, checks to see if players
 **              still have money and if they do, let them play again. 
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

int main() {

  int numOfPlayers;
  srand(time(NULL));
  
  cout << "Are you ready to play? - ";
  cout << "How many players? (1 - 4) - ";
  
  // Is player answer valid
  bool isValid = false;
  do {
  
    cin >> numOfPlayers;
    cout << endl;
    
    if (!(numOfPlayers <= 0 || numOfPlayers > 4)) {
    
      isValid = true;
    
    } else {
    
      cout << "That wasn't valid, try again - ";
    
    }
    
  } while (!isValid);
  
  cout << endl;
  
  player playerArray[numOfPlayers];
  
  // Determine starting balance and whether that answer is valid
  for (int i = 0; i < numOfPlayers; i++) {
  
    cout << "Player " << i + 1 << ", what's your starting balance? - ";
    cin >> playerArray[i].balance;
    
    if (!(playerArray[i].balance > 0)) {
    
      bool isValid = false;
      do {
      
        cout << "That wasn't valid, try again - ";
        cin >> playerArray[i].balance;
        
        if (playerArray[i].balance > 0) {
        
          isValid = true;
        
        }
      
      } while (!isValid);
    
    } 
    
    cout << endl;

  }
  
  // Run gameplay and if there's still money, ask if they want to play again
  int ans;
  bool satisfied = true;
  do {
  
    gamePlay(numOfPlayers, playerArray);
    
    bool canPlay = false;
    for (int i = 0; i < numOfPlayers; i++) {
    
      if (playerArray[i].balance > 0) {
      
        canPlay = true;
      
      }
    
    }
    
    if (canPlay) {
    
      cout << endl << "Would you like to play again? (1 - no, 0 - yes) - ";
      cin >> ans;
      cout << endl;
      
      
      bool isValid = false;
      do {
                
        if (ans != 1 && ans != 0) {
                
          cout << "That wasn't a proper answer, try again - ";
          cin >> ans;
          cout << endl;
                
        } else {
            
          satisfied = (bool)ans;
          isValid = true;
                
        }
        
      } while (!isValid);
    
    } else {
    
      satisfied = true;
    
    }
     
  } while (!satisfied);
  
  return 0;
}