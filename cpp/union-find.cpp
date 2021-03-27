#include <iostream>
#include <cstring>
using namespace std;

class Edge {
public:
    int src;
    int dest;
};

class Graph {
public:
    // cardinalities of sets of edges/vertices
    int V;
    int E;

    // array of edges in the graph
    Edge* edge;
};

Graph* init_graph(int v, int e) {
    Graph* g = new Graph();
    g->V = v;
    g->E = e;

    g->edge = new Edge[g->E * sizeof(Edge)];
    return g;
}

// if there is no current parent then it is `i`
// otherwise, we need to check the parent of `i`
// -- "finds" the elements of the subsets we want
int find_parent(int parent[], int i) {
    if (parent[i] == -1) return i;
    return find_parent(parent, parent[i]);
}

// -- takes the union of subsets found from calls to `find(...)`
void union_subsets(int parent[], int curr_src, int curr_dest) {
    parent[curr_src] = curr_dest;
}

// -- returns true if a Graph contains a cycle
bool contains_cycle(Graph* g) {
    // initialize V subsets as singletons with no parents
    int* parent = new int[g->V * sizeof(int)];
    memset(parent, -1, g->V * sizeof(int));

    // we need to check the vertices belonging to each edge
    // if we find two equal subsets, then we found a cycle
    for (int i = 0; i < g->E; ++i) {
        int curr_src = find_parent(parent, g->edge[i].src);
        int curr_dest = find_parent(parent, g->edge[i].dest);
        if (curr_src == curr_dest) {
            return true;
        }
        union_subsets(parent, curr_src, curr_dest);
    }
    return false;
}

int main() {
    int V = 3;
    int E = 3;

    Graph* g = init_graph(V, E);
    g->edge[0].src = 0;
    g->edge[0].dest = 1;

    g->edge[1].src = 1;
    g->edge[1].dest = 2;

    g->edge[2].src = 2;
    g->edge[2].dest = 3;

    if (contains_cycle(g)) {
        cout << "Failure:  A cycle was detected in the graph.\n";
    }
    else {
        cout << "Succcess: No cycles were detected in the graph.\n";
    }


    return 0;
}




























