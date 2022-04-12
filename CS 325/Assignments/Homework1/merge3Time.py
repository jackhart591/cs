import random
import time
from mergesort3 import mergesort3

def createlist(n):
    Data = [None] * n
    for i in range(n):
        Data[i] = random.randint(0, 10000)
    return Data


def main():
    
    for i in range(1, 11):
        list = createlist(5000 * i)
        past = time.time()
        mergesort3(list)
        current = time.time()
        print("Time for list with " + str(len(list)) + " elements:\t" + str(current - past))



if __name__ == "__main__":
    main()
