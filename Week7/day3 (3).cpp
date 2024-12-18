//Code Implementation of DFS for a Directed Graph
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

    // Add directed edges
    adjList[0].push_back(1); // Edge: 0 -> 1
    adjList[0].push_back(2); // Edge: 0 -> 2
    adjList[1].push_back(3); // Edge: 1 -> 3
    adjList[1].push_back(4); // Edge: 1 -> 4

    vector<bool> visited(nodes, false);

    cout << "DFS Traversal: ";
    dfs(0, adjList, visited); // Start DFS from node 0
    cout << endl;

    return 0;
}

