# Name: Jackson Hart
# Date: 4/12/2022
# Class: CS 325

index = 0

def GetNumber(line):
    num_str = ""
    global index

    while 1:
        char = line[index]
        index += 1

        if not char.isdigit(): # if char is a space
            break
        else:
            num_str += char
    
    return num_str

def parsedata():
    global index
    Data = []
    file = open("data.txt", "r")

    for line in file:
        index = 0
        num_str = GetNumber(line) # Get the length of the array
        Length = int(num_str)
        List = [None] * Length

        for i in range(Length):
            num_str = GetNumber(line)
            List[i] = int(num_str)

        Data.append(List)
    
    file.close()

    return Data

def printdata(Data):
    for list in Data:
        for elem in list:
            print(elem, end=" ")
        print()