import math

class graph:
    def __init__(self, vertices, edges):
        self.Vertices = vertices
        self.Edges = edges
        
    def GetTotalWeight(self):
        totalWeight = 0
        for edge in self.Edges:
            totalWeight += edge.Weight

        return totalWeight

    def addedge(self, edge):
        self.Edges.append(edge)

        if edge.Source not in self.Vertices:
            self.Vertices.append(edge.Source)

        if edge.Target not in self.Vertices:
            self.Vertices.append(edge.Target)

    def __eq__(self, other):
        if set(self.Vertices) == set(other.Vertices) == None:
            return True
        return False

class vertex:
    def __init__(self, leastWeightedEdge):
        self.LeastWeightedEdge = leastWeightedEdge

    def setedge(self, edge):
        if self.LeastWeightedEdge > edge:
            self.LeastWeightedEdge = edge

class edge:
    def __init__(self, source, target):
        self.Source = source
        self.Target = target
        self.Weight = w(source, target)

    def isEqual(self, other):
        if self.Source == other.Source or self.Source == other.Target:
            if self.Target == other.Source or self.Target == other.Target:
                return True
        return False

def w(one, two):
    return round(math.sqrt(pow((one[0] - two[0]), 2) + pow((one[1] - two[1]), 2)))

def func(e):
    return e.Weight

def FindSet(sets, vert):
    for set in sets:
        if vert in set:
            return set
    return None

def getmstweight(vertices):
    total_weight = 0
    edges = []
    comp_graph = graph(vertices, None)
    tree = graph([vertices[0]], [edge((0,0), (0,0))])

    while tree != comp_graph:
        minweight = math.inf
        minedge = None

        for source in tree.Vertices:
            for target in vertices:
                if target not in tree.Vertices:
                    if minweight > w(source, target):
                        minedge = edge(source, target)
                        minweight = w(source, target)
                        print(f"{minweight}")
        
        if minedge != None:
            tree.addedge(minedge)
            total_weight += minweight

    return total_weight
            
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