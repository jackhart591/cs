import random
import time
from stoogesort import StoogeSort

# Name: Jackson Hart
# Date: 4/12/2022
# Class: CS 325

def createlist(n):
    Data = [None] * n
    for i in range(n):
        Data[i] = random.randint(0, 10000)
    return Data


def main():
    
    for i in range(1, 11):
        list = createlist(50 * i)
        past = time.time()
        StoogeSort(list, 0, len(list)-1)
        current = time.time()
        print(str(len(list)) + "\t\t" + str(current - past))



if __name__ == "__main__":
    main()
