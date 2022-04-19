import time
import sys
from random import randint

# Name: Jackson Hart
# Date: 4/18/2022
# Class: CS 325

sys.setrecursionlimit(10000)

val = []
wt = []
V = [[]]

def GenerateData(n):
    global val
    global wt

    #Reset variables
    val = []
    wt = []

    for i in range(n):
        val.append(randint(1, 100))
        wt.append(randint(1, 100))

def knapsack_recursive(W, n):
    global val
    global wt

    if (W == 0 or n == 0):
        return 0

    if wt[n-1] > W:
        return knapsack_recursive(W, n-1)
    else:
        return max(val[n-1] + knapsack_recursive(W - wt[n-1], n-1), knapsack_recursive(W, n-1))

def knapsack_dynamic(W, n):
    global V
    V = [[0 for x in range(W+1)] for y in range(n+1)]

    for i in range(n+1):
        for w in range(W+1):
            if i == 0 or w == 0:
                continue
            elif wt[i-1] <= w:
                V[i][w] = max(val[i-1] + V[i-1][w-wt[i-1]], V[i-1][w])
            else:
                V[i][w] = V[i-1][w]
    
    return V[n][w]
        


def main():
    for i in range(10):
        n = 10 * (i + 1)
        GenerateData(n)

        past = time.time()
        max_rec = knapsack_recursive(100, n)
        current = time.time()
        rec_time = round(current - past, 4)

        print(f"N={n} W=100\tRec time = {rec_time}\tmax Rec = {max_rec}", flush=True)

    for i in range(10):
        n = 100000 * (i+1)
        GenerateData(n)

        past = time.time()
        max_dyn = knapsack_dynamic(100, n)
        current = time.time()
        dyn_time = round(current - past, 4)

        print(f"N={n} W=100\tDyn time = {dyn_time}\tmax Dyn = {max_dyn}", flush=True)



if __name__ == '__main__':
    main()