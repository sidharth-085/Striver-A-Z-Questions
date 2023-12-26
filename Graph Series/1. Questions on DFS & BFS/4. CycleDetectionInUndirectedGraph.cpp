#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Approach 1: DFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// In DFS method, we keep a parent argument to keep the track of previous node.
// And, when we get the node which is already visited and not equal to parent
// means we detected the cycle.

bool dfs(int startVertex, int parent, vector<vector<int>> &adjList, vector<int> &visited) {
    visited[startVertex] = 1;

    for (int neighbour : adjList[startVertex]) {
        if (!visited[neighbour]) {
            if (dfs(neighbour, startVertex, adjList, visited) == true) {
                return true;
            }
        }
        else if (visited[neighbour] == true && neighbour != parent) {
            return true;
        }
    }

    return false;
}

bool detectCycle(int n, vector<vector<int>> &adjList) {
    vector<int> visited(n, 0);
    
    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            if (dfs(vertex, 0, adjList, visited) == true) {
                return true;
            }
        }
    }

    return false;
}

// Approach 2: BFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// In BFS method, we keep a pair of current node and parent node in queue to 
// keep the track of previous node for every level.
// And, when we get the node which is already visited and not equal to parent
// means we detected the cycle.

bool bfs(int startVertex, vector<int> adjList[], vector<int> &visited) {
    visited[startVertex] = 1;
    
    queue<pair<int, int>> q;
    q.push({startVertex, -1});

    while (!q.empty()) {
        pair<int, int> top = q.front();
        q.pop();

        int tVertex = top.first;
        int tParent = top.second;

        for (int neighbour : adjList[tVertex]) {
            if (!visited[neighbour]) {
                visited[neighbour] = 1;
                q.push({neighbour, tVertex});
            }
            else if (visited[neighbour] == 1 && neighbour != tParent) {
                return true;
            }
        }
    }

    return false;
}

bool detectCycle(int n, vector<int> adjList[]) {
    vector<int> visited(n, 0);

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            if (bfs(vertex, adjList, visited) == true) {
                return true;
            }
        }
    }

    return false;
}