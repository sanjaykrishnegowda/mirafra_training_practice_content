/* Adjacency list representation of an directed graph in C++ */

#include <iostream>   // For input/output operations
#include <list>       // For using the list container (adjacency list)
#include <vector>     // For using the vector container (to store the adjacency list for each vertex)

using namespace std;  // To avoid writing "std::" before every standard library function

// Class to represent a directed graph
class Graph {
    int V;                     // Number of vertices in the graph
    vector<list<int>> adjList; // Adjacency list where each list stores neighbors of a vertex

public:
    // Constructor to initialize a graph with V vertices
    Graph(int V) {
        this->V = V;                   // Set the number of vertices
        adjList.resize(V);             // Resize the adjacency list vector to store V lists (one for each vertex)
    }

    // Function to add a directed edge from vertex u to vertex v
    void addEdge(int u, int v) {
        adjList[u].push_back(v);  // Add vertex v to the adjacency list of vertex u (directed edge from u to v)
    }

    // Function to print the adjacency list representation of the graph
    void printGraph() {
        // Loop through all vertices of the graph
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";  // Print the current vertex
            // Loop through all the neighbors (adjacent vertices) of the current vertex
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";  // Print each neighboring vertex connected to the current vertex
            }
            cout << endl;  // Move to the next line after printing all neighbors of the current vertex
        }
    }
};

int main() {
    // Create a graph with 5 vertices (labeled 0, 1, 2, 3, 4)
    Graph g(5);

    // Add directed edges between vertices
    g.addEdge(0, 1);  // Add directed edge from vertex 0 to vertex 1
    g.addEdge(0, 4);  // Add directed edge from vertex 0 to vertex 4
    g.addEdge(1, 2);  // Add directed edge from vertex 1 to vertex 2
    g.addEdge(1, 3);  // Add directed edge from vertex 1 to vertex 3
    g.addEdge(1, 4);  // Add directed edge from vertex 1 to vertex 4
    g.addEdge(3, 4);  // Add directed edge from vertex 3 to vertex 4

    // Print the adjacency list of the graph
    g.printGraph();

    return 0;  // Indicate successful program execution
}


