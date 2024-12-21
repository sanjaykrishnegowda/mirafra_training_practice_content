// kruskal algorith to find minimum spanning tree
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Function to create a graph with V vertices and E edges
Graph createGraph(int V, int E) {
    Graph graph;
    graph.V = V;
    graph.E = E;
    return graph;
}

// Find function for Union-Find (uses path compression)
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

// Union function for Union-Find
void unionSet(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Comparator function to sort edges by weight
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to find the MST using Kruskal's Algorithm
void kruskalMST(Graph& graph) {
    int V = graph.V;
    vector<Edge> result;  // To store the resulting MST
    int parent[V], rank[V];

    // Initialize Union-Find structures
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by weight
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    // Process edges in sorted order
    for (const Edge& edge : graph.edges) {
        int rootSrc = find(parent, edge.src);
        int rootDest = find(parent, edge.dest);

        // If including this edge doesn't form a cycle
        if (rootSrc != rootDest) {
            result.push_back(edge);
            unionSet(parent, rank, rootSrc, rootDest);
        }

        // Stop if we already have V-1 edges
        if (result.size() == V - 1)
            break;
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const Edge& edge : result) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
}

int main() {
    int V = 4;  // Number of vertices
    int E = 5;  // Number of edges

    Graph graph = createGraph(V, E);

    // Add edges (src, dest, weight)
    graph.edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(graph);

    return 0;
}
