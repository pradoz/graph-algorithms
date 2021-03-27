from collections import defaultdict

# undirected graph, adjacency list representation
class Graph:

    def __init__(self, vertices):
        self.V = vertices # number of vertices
        self.graph = defaultdict(list) # dictionary for each graph


    # adds an edge to the graph
    # every edge is a key
    # -- each value holds a list of all nodes it has an edge to
    def addEdge(self, u, v):
        self.graph[u].append(v)
        # if v not in self.graph[u]: self.graph[u].add(v)

    # helper function: finds the subset of an element i
    def find_parent(self, parent, i):
        if parent[i] == -1:
            return i
        if parent[i]!= -1:
            return self.find_parent(parent, parent[i])

    # checks whether a graph contains cycle
    def isCyclic(self):
        
        # helper function to find the union of two subsets
        def union(parent, x, y):
            parent[x] = y

        # Allocate memory for creating V subsets and
        # Initialize all subsets as single element sets
        parent = [-1] * self.V

        # Iterate through all edges of graph, find subset of both
        # vertices of every edge, if both subsets are same, then
        # there is cycle in graph.
        for i in self.graph:
            for j in self.graph[i]:
                x = self.find_parent(parent, i)
                y = self.find_parent(parent, j)
                if x == y:
                    return True
                union(parent, x, y)


# create the graph with 3 nodes and the edges:
#   0->1, 1->2, 2->0
g = Graph(5)
g.addEdge(0, 1)
g.addEdge(1, 2)
g.addEdge(2, 3)
g.addEdge(3, 4)

# check if the graph has a cycle
if g.isCyclic():
    print("A cycle was detected.")
else:
    print("No cycles were detected.")


