import math

def w(one, two):
    return math.floor(math.sqrt(pow((one[0] - two[0]), 2) + pow((one[1] - two[1]), 2)) + 0.5)

def getmstweight(vertices):
    weights = []
    tree = set()
    tree.add(vertices[0])

    #While the tree does not contain every node
    while tree != set(vertices):
        minKeyVal = math.inf
        idx = -1

        # Check every edge exiting the tree
        for source in tree:
            for i, target in enumerate(vertices):
                if source == target:
                    continue
                
                if target not in tree and minKeyVal > w(source, target):
                    minKeyVal = w(source, target)
                    idx = i

        # Once have the optimal edge, append
        weights.append(minKeyVal)
        tree.add(vertices[idx])

    return sum(weights)
            
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