// BFS for a Graph (Adjacency List) for undirected graph
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int startNode, vector<vector<int>>& adjList, vector<bool>& visited) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        cout << currentNode << " ";

        // Enqueue all unvisited neighbors
        for (int neighbor : adjList[currentNode]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int nodes = 5; // Number of nodes
    vector<vector<int>> adjList(nodes);

    // Add edges (Example for an undirected graph)
    adjList[0] = {1, 2};
    adjList[1] = {0, 3, 4};
    adjList[2] = {0};
    adjList[3] = {1};
    adjList[4] = {1};

    vector<bool> visited(nodes, false);

    cout << "BFS Traversal: ";
    bfs(0, adjList, visited); // Start BFS from node 0
    cout << endl;

    return 0;
}
