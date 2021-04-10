#include <iostream>

using namespace std;

int fib_rec(int n) {

  int sum = 0;
  
  if (n == 1) {
  
    return 0;
  
  } else if (n == 2) {
  
    return 1;
  
  } else {
  
    sum = fib_rec(n-1) + fib_rec(n-2);
    return sum;
  
  }

}

int fib_iter(int n){

  int first, second, hold;

  first = 0;
  second = 1;

  if (n == 0){

    second = 0;

  }

  else if (n == 1){

    second = 1;
  }

  else{
    for (int i = 0; i < n - 2; i++){

      hold = second;
      second = first + second;
      first = hold;

      //cout << second << endl;
    }
  }

  return second;
}


int main() {

  int input;
  cout << "What number do you want in the fibonacci sequence?: ";
  cin >> input;
  cout << endl;
  cout << "The number in this position is " << fib_rec(input) << endl;
  //cout << "The number in this position is " << fib_iter(input) << endl;
  return 0;

}