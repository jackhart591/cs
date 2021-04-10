#include <iostream>
#include <string>

/**********************************************************************************************************************
 ** Program Filename: Expense_Calc.cpp
 ** Author: Jackson Hart
 ** Date: 2/14/2021
 ** Description: User enters various expenses and program calculates what can be reimbursed and what needs to be payed 
 **              by the user. 
 ** Input: integers above 0, integers of time (0-24), and non-negative doubles
 ** Output: Total amount of money used, total amount to be reimbursed, total amount of money the user owes. 
 ** *******************************************************************************************************************/

using namespace std;

bool InputHandler();
void InputHandler(int& input, bool isTime);
void InputHandler(double& input);
void InputHandler(bool& usedCar, bool& usedTaxi);
void InitInitials (int& numOfDays, int& departTime, int& arrivalTime, double& airfare, double& confFees);
double CalcTravelExpenses(bool& usedCar, bool& usedTaxi, double& transpFees, int numOfDays);
void MealFee(double& mealFees, double& mealExpense, double& mealReimb, int departTime, int arrivalTime, int numOfDays);
void UpdateTotal(double& totalExpense, double& totalReimbursement, double expenseToAdd, double reimbursementToAdd);

/** ********************************************************************************************************************
 ** Function: main
 ** Description: Runs necessary functions to calculate the numbers, outputs the numbers to the user, and loops if the
 **              user wants to play again
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

int main() {
  
  bool playAgain;
  
  int numOfDays, departTime, arrivalTime;
  double totalExpense, totalReimb, airfare, confFees, transpFees, mealFees;
  double mealReimb = 0;
  double totalMealExcess = 0;
  bool usedCar, usedTaxi;
  
  do {
    
    InitInitials(numOfDays, departTime, arrivalTime, airfare, confFees); 
    
    double totalTravelExcess = CalcTravelExpenses(usedCar, usedTaxi, transpFees, numOfDays);
    MealFee(mealFees, totalMealExcess, mealReimb, departTime, arrivalTime, numOfDays);
    
    UpdateTotal(totalExpense, totalReimb, (airfare + confFees + transpFees + mealFees), ((airfare + confFees + transpFees + mealFees) - (totalTravelExcess + totalMealExcess)));
    
    cout << "Your total expense for this trip is: " << totalExpense << endl;
    cout << "Your total reimbursement for this trip is: " << totalReimb << endl;
    cout << "You need to pay: $" << (totalExpense - totalReimb) << endl;
    cout << "Do you want to play again (0-no or 1-yes)? ";
    playAgain = InputHandler();
  
  } while (playAgain);
  return 0;

}

/***********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Checks to make sure a valid boolean input was entered.
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

bool InputHandler() {

  int input;
  cin >> input;
  
  // Makes sure it's an bool
  if (cin.fail()) {
  
    do {
      
      cin.clear();
      cin.ignore(256, '\n');
      cout << endl << "That wasn't a valid input, try again - ";
      cin >> input;
    
    } while (cin.fail());
  
  }
  
  // Recalls input if it isn't 0 or 1
  if (input != 0 && input != 1) {
  
    cout << "That wasn't a 0 or 1, try again - ";
    InputHandler();
  
  } else {
  
    return input == 1 ? true : false;
  
  }

}

/***********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Checks to make sure user entered valid int, then makes sure it fits the context based on if its time 
 **              or amount of days
 ** Parameters: reference to input, boolean isTime, boolean isDays
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void InputHandler(int& input, bool isTime, bool isDays) {

  cin >> input;
  
  // Makes sure it's an integer
  if (cin.fail()) {
  
    do {
      
      cin.clear();
      cin.ignore(256, '\n');
      cout << endl << "That wasn't a valid input, try again - ";
      cin >> input;
    
    } while (cin.fail());
  
  }
  
  // Recalls input if time isn't real
  if (isTime) {
  
    if (input > 24 || input < 0) {

        cout << endl << "That isn't a real time, try again - ";
        InputHandler(input, true, false);
    
    }
  
  // Makes sure user doesn't input 0 days
  } else if (isDays) {
  
    if (input <= 0) {
    
      cout << endl << "It can't be 0 days, try again - ";
      InputHandler(input, false, true);
    
    }
  
  }

}

/***********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Makes sure user inputs a valid monetary amount (not negative and not a string)
 ** Parameters: reference to double input 
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void InputHandler (double& input) {

  cin >> input;
  
  // Makes sure it's a double
  if (cin.fail()) {
  
    do {
      
      cin.clear();
      cin.ignore(256, '\n');
      cout << endl << "That wasn't a valid input, try again - ";
      cin >> input;
    
    } while (cin.fail());
  
  }
  
  // Makes sure it's above 0
  if (input < 0) {
  
    cout << "Numbers can't be negative, try again - ";
    InputHandler(input);
  
  }

}

/***********************************************************************************************************************
 ** Function: InputHandler
 ** Description: Takes in the user's input for whether they used a bool or taxi, makes sure it's valid, then puts it in
 **              a way the program understands
 ** Parameters: reference to usedCar, reference to usedTaxi
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void InputHandler(bool& usedCar, bool& usedTaxi) {

  int input;
  cin >> input;
  
  // Makes sure it's an integer
  if (cin.fail()) {
  
    do {
      
      cin.clear();
      cin.ignore(256, '\n');
      cout << endl << "That wasn't a valid input, try again - ";
      cin >> input;
    
    } while (cin.fail());
  
  }
  
  // Recalls input if it isn't 1 or 2
  if (input != 1 && input != 2) {
  
    cout << "That wasn't a 1 or 2, try again - ";
    InputHandler(usedCar, usedTaxi);
  
  } else {
  
    usedCar = input == 1 ? true : false;
    usedTaxi = input == 2 ? true : false;
  
  }

}

/***********************************************************************************************************************
 ** Function: InitInitials
 ** Description: Collects input that doesn't need to be looped through as with the meals and hotel.
 ** Parameters: reference to the number of days, reference to the depart time, reference to the arrival time, reference
 **              to the airfare, and reference to the conference fees
 ** Pre-Conditions: all parameters have to have been declared
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void InitInitials (int& numOfDays, int& departTime, int& arrivalTime, double& airfare, double& confFees) {

  cout << "Enter the number of days on your trip: ";
  InputHandler(numOfDays, false, true);
  cout << endl << endl;
    
  
  cout << "Enter your departure time (just the hour) on the first day in 24-hour format (i.e., 16 for 4pm): ";
  InputHandler(departTime, true, false);
    
  cout << "Enter your arrival time (just the hour) on the last day in 24-hour format (i.e., 16 for 4pm): ";
  InputHandler(arrivalTime, true, false);
  cout << endl << endl;
    
    
  cout << "Enter total amount of airfare, in $: ";
  InputHandler(airfare);
  
  cout << "Enter total conference or seminar fees, in $: ";
  InputHandler(confFees);
  cout << endl << endl;

}

/***********************************************************************************************************************
 ** Function: TranspFacility
 ** Description: Runs through the travel fees based on what type of travel necessity it was and determines what can be
 **              reimbursed and what can't
 ** Parameters: reference to the amount for reimbursement on daily fees, reference to the total transportation fees, 
 **             the number of days, and a string of the type of facility (can be car, taxi, or hotel)
 ** Pre-Conditions: You must know what facilities the user used
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void TranspFacility (double& reimbDailyFee, double& transpFees, int numOfDays, string fac) {

  // if we're talking about the car or taxi
  if (fac.compare("car") == 0 || fac.compare("taxi") == 0) {
  
    // figure out rental fees if using the car
    if (fac.compare("car") == 0) {
    
      cout << "Enter your total car rental fee, including gas fee, in $: ";
      InputHandler(transpFees);
      reimbDailyFee += transpFees;
      cout << endl << endl;
    
    }
  
    // figure out how much they had to pay daily
    for (int i = 0; i <= numOfDays-1; i++) {
  
      if (fac.compare("car") == 0) {
      
        cout << "Enter your parking fee for day " << i + 1 << ", in $: "; 
      
      } else if (fac.compare("taxi") == 0) {
      
        cout << "Enter your taxi fee for day " << i + 1 << ", in $: ";
      
      }
      
      double amount;
      InputHandler(amount);
      transpFees += amount;
        
      // determine how much of that can be reimbursed (max $6 per day)
      reimbDailyFee += amount <= 6 ? amount : 6; 
  
    }
  
  // if we're talking about the hotel
  } else if (fac.compare("hotel") == 0) {
    
    // figure out how much they spent per night (they don't spend the last night on vacation)
    for (int i = 0; i <= numOfDays-2; i++) {
  
      cout << "Enter your hotel fee for night " << i + 1 << ", in $: ";
      double amount;
      InputHandler(amount);
      
      // determine how much can be reimbursed (max $90 per night)
      reimbDailyFee += amount <= 90 ? amount : 90;
      transpFees += amount;
  
    }
  
  }

}

/***********************************************************************************************************************
 ** Function: CalcTravelExpenses
 ** Description: Determines what facilities the user used, runs the TranspFacility function accordingly, and then 
 **              returns the excess that needs to be paid
 ** Parameters: reference to whether the user used a car, reference to whether the user used a taxi, reference to
 **             transportation fees, number of days on trip
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

double CalcTravelExpenses(bool& usedCar, bool& usedTaxi, double& transpFees, int numOfDays) {

  cout << "Did you 1: rent a car or 2: use taxi during your trip? Enter 1 or 2: ";
  InputHandler(usedCar, usedTaxi);
  cout << endl << endl;
  
  double reimbDailyFee = 0;
  
  if (usedCar) {
  
    TranspFacility(reimbDailyFee, transpFees, numOfDays, "car");
  
  } else if (usedTaxi) {
    
    TranspFacility(reimbDailyFee, transpFees, numOfDays, "taxi"); 
  
  }
  
  cout << endl << endl;
  
  TranspFacility(reimbDailyFee, transpFees, numOfDays, "hotel");
  
  cout << endl << endl;
  
  // returns what needs to be paid for
  return transpFees - reimbDailyFee;

}

/************************************************************************************************************************
 ** Function: Meal
 ** Description: Determines how much any given meal cost
 ** Parameters: reference to total meal fees, reference to total amount that can be reimbursed daily, and what meal
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void Meal(double& mealFees, double& reimbDailyFee, int meal) {

  double amount;
  switch (meal) {
  
    case 1:
      cout << "Enter breakfast fee, in $: ";
      InputHandler(amount);
      mealFees += amount;
      reimbDailyFee += amount <= 9 ? amount : 9;
      break;
    case 2:
      cout << "Enter lunch fee, in $: ";
      InputHandler(amount);
      mealFees += amount;
      reimbDailyFee += amount <= 12 ? amount : 12;
      break;
    case 3:
      cout << "Enter dinner fee, in $: ";
      InputHandler(amount);
      mealFees += amount;
      reimbDailyFee += amount <= 16 ? amount : 16;
      break;
  
  }

}

/***********************************************************************************************************************
 ** Function: FirstMeal
 ** Description: Determines which meals the user can get paid back on based on when they departed and then runs the meal
 **              function accordingly 
 ** Parameters: reference to total meal fees, reference to amount that can be reimbursed for meals daily, which meal
 **             they're in time for
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void FirstMeal (double& mealFees, double& reimbDailyFee, int meals) {

  switch (meals) {
      
    case 0:
      cout << "Your breakfast for day 1 is not allowed for reimbursement." << endl << "Your lunch for day 1 is not allowed for reimbursement." << endl << "Your dinner for day 1 is not allowed for reimbursement." << endl << endl;
      cout << endl << endl;
      break;
        
    case 1:
      Meal(mealFees, reimbDailyFee, 1);
      Meal(mealFees, reimbDailyFee, 2);
      Meal(mealFees, reimbDailyFee, 3);
      cout << endl << endl;
      break;
          
    case 2:
      cout << "Your breakfast for day 1 is not allowed for reimbursement." << endl;
      Meal(mealFees, reimbDailyFee, 2);
      Meal(mealFees, reimbDailyFee, 3);
      break;
        
    case 3:
      cout << "Your breakfast for day 1 is not allowed for reimbursement." << endl << "Your lunch for day 1 is not allowed for reimbursement." << endl;
      Meal(mealFees, reimbDailyFee, 3);
      break;
  }

} 

/***********************************************************************************************************************
 ** Function: LastMeal
 ** Description: Determines which meals the user can get paid back on based on when they arrived home and then runs the
 **              meal function accordingly 
 ** Parameters: reference to total meal fees, reference to amount that can be reimbursed for meals daily, which meal
 **             they're in time for
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void LastMeal (double& mealFees, double& reimbDailyFee, int meals) {

  switch (meals) {
      
    case 0:
      cout << "Your breakfast for day 1 is not allowed for reimbursement." << endl << "Your lunch for day 1 is not allowed for reimbursement." << endl << "Your dinner for day 1 is not allowed for reimbursement." << endl << endl;
      break;
        
    case 1:
      Meal(mealFees, reimbDailyFee, 1); 
      cout << "Your lunch for day 1 is not allowed for reimbursement." << endl << "Your dinner for day 1 is not allowed for reimbursement." << endl << endl;
      break;
          
    case 2:
      Meal(mealFees, reimbDailyFee, 1);
      Meal(mealFees, reimbDailyFee, 2);
      cout << "Your dinner for day 1 is not allowed for reimbursement." << endl << endl;
      break;
        
    case 3:
      Meal(mealFees, reimbDailyFee, 1);    
      Meal(mealFees, reimbDailyFee, 2);
      Meal(mealFees, reimbDailyFee, 3);
      cout << endl << endl;
      break;
      
    }

}

/***********************************************************************************************************************
 ** Function: MealFee
 ** Description: Puts the time of arrival/departure into the terms of meals so which meal they can get paid for can be
 **              determined, and calls all the necessary functions for figuring that out
 ** Parameters: reference to total meal fees, reference to the total excess left over after reimbursments, reference to 
 **             amount that can be reimbursed for meals daily, departure time, arrival time, number of days on trip
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void MealFee(double& mealFees, double& mealExpense, double& reimbDailyFee, int departTime, int arrivalTime, int numOfDays) {

  // For every day that they were here
  for (int i = 0; i < numOfDays; i++) {
    
    cout << "Day " << i + 1 << endl; 
    // if it was the first day
    if (i == 0) {
      
      int meals = 0;
      // determine which meal they can get based on when they departed
      meals = departTime <= 7 ? 1 : (departTime <= 12 ? 2 : (departTime <= 18 ? 3 : 0));
      FirstMeal(mealFees, reimbDailyFee, meals);

    // or if it was the last day
    } else if (i == (numOfDays-1)) {
      
      int meals = 0;
      // same thing here but based on when the arrived
      meals = arrivalTime >= 8 ? (arrivalTime >= 13 ? (arrivalTime >= 19 ? 3 : 2) : 1) : 0;
      LastMeal(mealFees, reimbDailyFee, meals);
      
    // if it isn't the first or last day, just let them have all of them
    } else {
      
      Meal(mealFees, reimbDailyFee, 1);    
      Meal(mealFees, reimbDailyFee, 2);
      Meal(mealFees, reimbDailyFee, 3);
      cout << endl << endl;
      
    }
  
  }
  
  // Sets meal expense equal to amount left over that the user has to pay
  mealExpense = mealFees - reimbDailyFee;

}

/***********************************************************************************************************************
 ** Function: Update Total
 ** Description: sets total expense and total reimbursement equal to the values expense to add and reimbursement to add
 **              respectively
 ** Parameters: reference to total amount spent, reference to total amount that can be reimbursed, total amount to set
 **             total expense equal to, amount to set total reimbursement equal to
 ** Pre-Conditions: none
 ** Post-Conditions: none 
 ** ********************************************************************************************************************/

void UpdateTotal(double& totalExpense, double& totalReimbursement, double expenseToAdd, double reimbursementToAdd) {

  totalExpense = expenseToAdd;
  totalReimbursement = reimbursementToAdd;

}
