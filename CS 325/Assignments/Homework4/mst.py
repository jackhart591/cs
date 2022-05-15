import math

def w(one, two):
    return math.floor(math.sqrt(pow((one[0] - two[0]), 2) + pow((one[1] - two[1]), 2)) + 0.5)

def UpdateKeys(vertices, keys, idx):
    currentVal = keys[idx]

    for i in range(len(keys)):
        if (currentVal + w(vertices[idx], vertices[i])) < keys[i]:
            keys[i] = currentVal + w(vertices[idx], vertices[i])

    print(keys)

def getmstweight(vertices):
    vert_keys = [math.inf] * len(vertices)
    vert_keys[0] = 0
    tree = set()
    weight_total = 0

    #While the tree does not contain every node
    while tree != set(vertices):
        minKeyVal = math.inf
        idx = -1

        #Find min key
        for i, vals in enumerate(vert_keys):
            if vertices[i] not in tree and minKeyVal > vals:
                minKeyVal = vals
                idx = i

        weight_total += minKeyVal
        tree.add(vertices[idx])
        UpdateKeys(vertices, vert_keys, idx)

    return weight_total
            
def main():
    file = open('graph.txt', 'r')

    testcases = int(file.readline())

    for i in range(testcases):
        numverts = int(file.readline())
        vertices = []
        for j in range(numverts):
            line = file.readline()
            idx = 0
            coord = [-1, -1]
            for j in range(2):
                numstr = ""
                while 1:
                    if not line[idx].isdigit():
                        idx += 1
                        break
                    else:
                        numstr += line[idx]
                        idx += 1
                coord[j] = int(numstr)
            vertices.append(tuple(coord))
        print(f'Test case {i+1}: MST weight {getmstweight(vertices)}')

    file.close()

if __name__ == '__main__':
    main()