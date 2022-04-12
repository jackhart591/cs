from ParseData import parsedata
import sys

sys.setrecursionlimit(1000)

def merge(Data, Bot, Mid, Top):
    idx = i = j = k = 0

    if (Bot is None):
        Bot = []

    if (Mid is None):
        Mid = []
    
    if (Top is None):
        Top = []
    
    while i < len(Bot) and j < len(Mid) and k < len(Top):
        if (Bot[i] <= Mid[j] and Bot[i] <= Top[k]):
            Data[idx] = Bot[i]
            i += 1
        elif (Mid[j] <= Top[k] and Mid[j] <= Bot[i]):
            Data[idx] = Mid[j]
            j += 1
        else:
            Data[idx] = Top[k]
            k += 1
        idx += 1

    # If there's any remaining elements
    while (i < len(Bot) and j < len(Mid)):
        if (Bot[i] <= Mid[j]):
            Data[idx] = Bot[i]
            i += 1
        else:
            Data[idx] = Mid[j]
            j += 1
        idx += 1

    while (k < len(Top) and j < len(Mid)):
        if (Top[k] <= Mid[j]):
            Data[idx] = Top[k]
            k += 1
        else:
            Data[idx] = Mid[j]
            j += 1
        idx += 1

    while (i < len(Bot) and k < len(Top)):
        if (Bot[i] <= Top[k]):
            Data[idx] = Bot[i]
            i += 1
        else:
            Data[idx] = Top[k]
            k += 1
        idx += 1

    while (i < len(Bot)):
        Data[idx] = Bot[i]
        i += 1
        idx += 1

    while (j < len(Mid)):
        Data[idx] = Mid[j]
        j += 1
        idx += 1

    while (k < len(Top)):
        Data[idx] = Top[k]
        k += 1
        idx += 1

    return Data


def mergesort3(Data):
    if len(Data) > 1:
        third = (len(Data) // 3) + 1 # Gets 1/3

        Bottom = mergesort3(Data[:third]) # 1/3
        Third = mergesort3(Data[third:(2*third)]) # 2/3
        Top = mergesort3(Data[(2*third):]) # 3/3
        Data = merge(Data, Bottom, Third, Top)

    return Data

def main():

    Data = parsedata()

    print("Unsorted Data:")
    for d in Data:
        print(d)
    
    for i, List in enumerate(Data): # Sort each list
        Data[i] = mergesort3(List)
    
    print("\nSorted Data:")
    for d in Data:
        print(d)


if __name__ == "__main__":
    main()