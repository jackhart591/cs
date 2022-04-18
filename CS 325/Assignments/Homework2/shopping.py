index = 0
val = []
wt = []
family = []
V = []

def getnumber(line):
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

def parsetext(file):
    global val 
    global wt
    global family

    val = []
    wt = []
    family = []

    num_items = int(file.readline())
    for j in range(num_items):
        global index
        index = 0
        line = file.readline()

        val.append(int(getnumber(line)))
        wt.append(int(getnumber(line)))
    
    num_members = int(file.readline())
    for k in range(num_members):
        family.append(int(file.readline()))

def knapsack(W, n):
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

def get_items(W, n):
    i = n
    k = W
    items = []

    while i > 0 and k > 0:
        if V[i][k] != V[i-1][k]:
            items.append(i)
            i -= 1
            k = k - wt[i]
        else:
            i -= 1

    return items

def main():
    global val
    global wt
    global family

    file = open("shopping.txt", "r")
    num_cases = int(file.readline())

    for i in range(num_cases):
        parsetext(file)

        total_value = 0
        items = []
        for member in family:
            total_value += knapsack(member, len(val))
            items.append(get_items(member, len(val)))

        print(f"Test Case {i+1}")
        print(f"Total price {total_value}")

        for j in range(len(family)):
            print(f"{j+1}:", end=" ")

            for item in items[j]:
                print(item, end=" ")

            print()
        print()
    



if __name__ == "__main__":
    main()