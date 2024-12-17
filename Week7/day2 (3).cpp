/* Adjacency matrix representation of an directed graph in C++ */

#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

public:
    // Constructor to initialize the graph with V vertices
    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, 0)); // Resize the matrix with all elements initialized to 0
    }

    // Function to add a directed edge from vertex u to vertex v
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1; // Set matrix[u][v] to 1 to represent the directed edge from u to v
    }

    // Function to print the adjacency matrix of the graph
    void printGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " "; // Print 1 if there's an edge, 0 otherwise
            }
            cout << endl; // Newline after each row
        }
    }
};

int main() {
    // Create a directed graph with 5 vertices (0 to 4)
    Graph g(5);

    // Add directed edges
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 4);

    // Print the adjacency matrix of the graph
    cout << "Adjacency Matrix for Directed Graph:" << endl;
    g.printGraph();

    return 0;
}
