//  finding minimum spanning tree Prim's Algorithm
#include <iostream>
#include <vector>
#include <climits> // For INT_MAX

using namespace std;

// Function to find the vertex with the minimum key value
int findMinKeyVertex(vector<int>& key, vector<bool>& inMST, int V) {
    int minKey = INT_MAX, minIndex;

    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the MST
void printMST(vector<int>& parent, vector<vector<int>>& graph, int V) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << "\n";
    }
}

// Prim's Algorithm
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V);         // To store the MST
    vector<int> key(V, INT_MAX);   // To store the minimum edge weight for each vertex
    vector<bool> inMST(V, false); // To track vertices included in MST

    key[0] = 0;     // Start from the first vertex
    parent[0] = -1; // Root of MST has no parent

    for (int count = 0; count < V - 1; count++) {
        int u = findMinKeyVertex(key, inMST, V); // Find the vertex with the minimum key
        inMST[u] = true;

        // Update the key and parent for the adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, V);
}

int main() {
    // Number of vertices in the graph
    int V = 5;

    // Graph represented as an adjacency matrix
    vector<vector<int>> graph = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}};

    primMST(graph, V);

    return 0;
}
