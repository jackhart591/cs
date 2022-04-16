from random import randint

val = []
wt = []

def GenerateData(n):
    for i in range(n):
        val.append(randint(1, 100))
        wt.append(randint(1, 100))

def knapsack_recursive(W, n):
    if (W == 0 or n == 0):
        return 0

    if wt[n-1] > W:
        return knapsack_recursive(W, n-1)
    else:
        return max(val[n-1] + knapsack_recursive(W - wt[n-1], n-1), knapsack_recursive(W, n-1))

def knapsack_dynamic(W, n):
    V = [[] * W] * n

    for w in range(0, W):
        V[w][0] = 0

    for i in range(0, n):
        V[0][n] = 0
        for w in range(1, W):
            if wt[i] <= w:
                if val[i] + V[i-1][w - wt[i]] > V[i-1][w]:
                    V[i][w] = val[i] + V[i-1][w - wt[i]]
                else:
                    V[i][w] = V[i-1][w]
            else:
                V[i][w] = V[i-1][w]
        


def main():
    #GenerateData(100)
    global val
    val = [3, 4, 5, 15, 16]
    global wt
    wt = [2, 3, 4, 5, 10]
    print(knapsack_dynamic(13, 5))

if __name__ == '__main__':
    main()