#include <iostream>
#include <stdlib.h>

int inputHandler() {
    int temp;
    std::cout << "How long would you like your array to be? - ";
    std::cin >> temp;

    if (!std::cin.fail() && temp > 0 && temp <= 25) {
        return temp;
    } else { return inputHandler(); }
}

void MergeSort(int*& arr, int size) {
    int* temp = new int[size];

    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    if (size > 1) {
        int *temp1 {new int[size/2]}, *temp2 {new int[size-(size/2)]};

        for (int i = 0; i < size/2; i++) { // split
            temp1[i] = temp[i];
        }

        for (int i = 0; i < size-(size/2); i++) {
            temp2[i] = temp[i+size/2];
        }

        //sort
        MergeSort(temp1, size/2);
        MergeSort(temp2, size-(size/2));

        int i {0}, j{0}, k{0};
        do {
            if (j < size/2) {
                if (k < size-(size/2)) {
                    if (temp1[j] < temp2[k]) {
                        temp[i] = temp1[j];
                        j++;
                    } else {
                        temp[i] = temp2[k];
                        k++;
                    }
                    i++;
                } else {
                    temp[i] = temp1[j];
                    i++; j++;
                }
            } else {
                temp[i] = temp2[k];
                i++; k++;
            }
        } while (i < size);

        delete [] temp1;
        delete [] temp2;
        temp1 = NULL;
        temp2 = NULL;

        for (int i = 0; i < size; i++) {
            arr[i] = temp[i];
        }
        delete [] temp;
        temp = NULL;

    } else {
        delete [] temp;
        temp = NULL;
        return;
    }
} 

bool GetPrime(int num, int max) {
    for (int i = 1; i < max+1; i++) {
        if (num % i == 0 && num != i && i != 1) {
            return false;
        }
    }

    return true;
}

int main() {

    srand(time(NULL));

    int size = inputHandler();
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1;
        std::cout << "Array value at " << i+1 << ": " << arr[i] << std::endl;
    }

    std::cout << std::endl << "Sorting..." << std::endl << std::endl;
    MergeSort(arr, size);

    for (int i = 0; i < size; i++) {
        std::cout << "Array value at " << i+1 << ": " << arr[i] << std::endl;
    }

    std::cout << std::endl << "Getting Prime Numbers..." << std::endl << std::endl;

    for (int i = 0; i < size; i++) {
        if (GetPrime(arr[i], 100)) {
            std::cout << arr[i] << " ";
        }
    }

    std::cout << std::endl;

    delete [] arr;

    return 0;
}