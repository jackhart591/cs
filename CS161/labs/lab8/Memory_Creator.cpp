#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>

using namespace std;

int* CreateMemOne (int size) {

  int* arr = new int[size];
  
  return arr;
  
}

void CreateMemTwo (int** ptr_arr, int size) {

  *ptr_arr = new int[size];
}

void CreateMemThree (int*& ptr_arr, int size) {

  ptr_arr = new int[size];
  
}




int main () {

  int* arr2;
  int* arr3;
  
  int* arr1 = CreateMemOne(5);
  CreateMemTwo(&arr2, 50);
  CreateMemThree(arr3, 100);

  delete [] arr1;
  delete [] arr2;
  delete [] arr3;

  arr1 = NULL;
  arr2 = NULL;
  arr3 = NULL;

  return 0;
  
}