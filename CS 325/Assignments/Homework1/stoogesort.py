from ParseData import parsedata
from math import floor
import sys

sys.setrecursionlimit(1000)

def StoogeSort(Data, bottom, top):
    if Data[bottom] > Data[top]: # Swap data
        Data[bottom], Data[top] = Data[top], Data[bottom]
    
    if (top - bottom + 1) >= 3:
        moe = (top - bottom + 1) // 3 # Gets 1/3

        StoogeSort(Data, bottom, top - moe) # Bottom 2/3
        StoogeSort(Data, moe+bottom, top) # Top 2/3
        StoogeSort(Data, bottom, top - moe) # Bottom 2/3
    else:
        return

def main():
    
    Data = parsedata()

    print("Unsorted Data:")
    for d in Data:
        print(d)

    for List in Data: # Sort each list
        StoogeSort(List, 0, len(List)-1)

    print("\nSorted Data:")
    for d in Data:
        print(d)


if __name__ == "__main__":
    main()
