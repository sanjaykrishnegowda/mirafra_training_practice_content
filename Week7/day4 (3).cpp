//Code Implementation of DFS for a unDirected Graph
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int startNode, vector<vector<int>>& adjList, vector<bool>& visited) {
    stack<int> s;
    s.push(startNode);

    while (!s.empty()) {
        int currentNode = s.top();
        s.pop();

        if (!visited[currentNode]) {
            visited[currentNode] = true;
            cout << currentNode << " ";

            // Push neighbors to the stack
            for (auto neighbor : adjList[currentNode]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}

int main() {
    int nodes = 5; // Number of nodes
    vector<vector<int>> adjList(nodes);

    // Add edges (example for an undirected graph)
    adjList[0] = {1, 2};
    adjList[1] = {0, 3, 4};
    adjList[2] = {0};
    adjList[3] = {1};
    adjList[4] = {1};

    vector<bool> visited(nodes, false);

    cout << "DFS Traversal: ";
    dfs(0, adjList, visited); // Start DFS from node 0
    cout << endl;

    return 0;
}
