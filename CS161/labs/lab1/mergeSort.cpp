#include <iostream>

using namespace std;

// takes an array, splits it in two, sorts it, recombines
int splitSort(int arr[], int beg, int mid, int end) {

  int num1 = mid - beg + 1;
  int num2 = end - mid;
  
  int arr_temp1[num1], arr_temp2[num2]; // Creates two temporary arrays to use during merging process
  
  for (int i = 0; i < num1; i++) 
    arr_temp1[i] = arr[beg + i];
  for (int j = 0; j < num2; j++)
    arr_temp2[j] = arr[mid + 1 + j];
    
  int ind_temp1 = 0;
  int ind_temp2 = 0;
  int ind_arr = beg;
  
  /* 
  
    While the index of the beg temp array is less than it's max and same with the second, check to see which one is larger and set merge array to that
    Then plus everything out. 
  
  */
  while (ind_temp1 < num1 && ind_temp2 < num2) {
  
    if(arr_temp1[ind_temp1] <= arr_temp2[ind_temp2]) {
    
      arr[ind_arr] = arr_temp1[ind_temp1];
      ind_temp1++;
    
    } else {
    
      arr[ind_arr] = arr_temp2[ind_temp2];
      ind_temp2++;
    
    }
    ind_arr++;
  
  }
  
  while (ind_temp1 < num1) {
  
    arr[ind_arr] = arr_temp1[ind_temp1];
    ind_arr++;
    ind_temp1++;
  
  }
  
  while (ind_temp2 < num2) {
  
    arr[ind_arr] = arr_temp2[ind_temp2];
    ind_arr++;
    ind_temp2++;
  
  }
  
}

// Takes an array, splits, the array recursively until it's in the smallest possible pieces and then calls splitSort()
int mergeSort(int arr[], int beg, int end) {

  if (beg >= end) {
  
    return 0;
  
  }
  
  int mid = (beg + end - 1) / 2; 
  mergeSort(arr, beg, mid);
  mergeSort(arr, mid+1, end);
  splitSort(arr, beg, mid, end);

}

int main() {
  
  int arr[10];
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < 10; i++) {
  
    cout << "Enter a number - ";
    cin >> arr[i];
    cout << endl;
  
  }
  
  cout << "Processing..." << endl;
  mergeSort(arr, 0, arr_size - 1);
  for (int i = 0; i < arr_size; i++) {
  
    cout << arr[i] << endl;
  
  }
  

  return 0;
}