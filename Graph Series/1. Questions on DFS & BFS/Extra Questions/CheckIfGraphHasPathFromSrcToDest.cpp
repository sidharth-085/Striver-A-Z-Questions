#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// BFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

bool hasPathBFS(int startVertex, int dest, vector<int> &visited, vector<vector<int>> &graph) {
    visited[startVertex] = 1;

    queue<int> q;
    q.push(startVertex);

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        if (top == dest) {
            return true;
        }

        for (int &neighbour : graph[top]) {
            if (!visited[neighbour]) {
                visited[neighbour] = 1;
                q.push(neighbour);
            }
        }
    }

    return false;
}

// DFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

bool hasPathDFS(int startVertex, int dest, vector<int> &visited, vector<vector<int>> &graph) {
    if (startVertex == dest) {
        return true;
    }

    visited[startVertex] = 1;

    for (int &neighbour : graph[startVertex]) {
        if (!visited[neighbour]) {
            if (hasPathDFS(neighbour, dest, visited, graph) == true) {
                return true;
            }
        }
    }

    return false;
}

bool validPath(int n, vector<vector<int>>& edges, int src, int dest) {
    vector<vector<int>> graph(n);

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    vector<int> visited(n, 0);

    return hasPathDFS(src, dest, visited, graph);
}