/* Adjacency list representation of an undirected graph in C++ */

#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Class to represent a graph
class Graph {
    int V; // Number of vertices
    vector<list<int>> adjList; // Adjacency list

public:
    // Constructor
    Graph(int V) {
        this->V = V;
        adjList.resize(V); // Resize adjacency list to fit number of vertices
    }

    // Function to add an edge in an undirected graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add v to u's list
        adjList[v].push_back(u); // Add u to v's list (for undirected graph)
    }

    // Function to print the graph's adjacency list
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 4);

    // Print the graph
    g.printGraph();

    return 0;
}
