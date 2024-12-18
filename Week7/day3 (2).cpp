//Code Implementation of BFS for a Directed Graph
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

        // Traverse all directed neighbors of the current node
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

    // Add directed edges
    adjList[0] = {1, 2};
    adjList[1] = {3, 4};
    adjList[2] = {};
    adjList[3] = {};
    adjList[4] = {};

    vector<bool> visited(nodes, false);

    cout << "BFS Traversal (Directed Graph): ";
    bfs(0, adjList, visited); // Start BFS from node 0
    cout << endl;

    return 0;
}
