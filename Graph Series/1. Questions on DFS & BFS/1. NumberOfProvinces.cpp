#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Approach 1: DFS Algorithm
// Time Complexity: O(V + E)
// Space Complexity: O(V)

void dfs(int startVertex, int n, vector<vector<int>> &graph, vector<int> &visited) {
    visited[startVertex] = 1;

    for (int neighbour = 0; neighbour < n; neighbour++) {
        if (startVertex != neighbour && graph[startVertex][neighbour] == 1 && !visited[neighbour]) {
            dfs(neighbour, n, graph, visited);
        }
    }
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();

    vector<int> visited(n, 0);

    int count = 0;

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfs(vertex, n, isConnected, visited); 
            count++;
        }
    }
    
    return count;
}

// Approach 2: BFS Algorithm
// Time Complexity: O(V + E)
// Space Complexity: O(V)

void bfs(int startVertex, int n, vector<vector<int>> &roads, vector<int> &visited) {
    visited[startVertex] = 1;

    queue<int> q;
    q.push(startVertex);

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        for (int neighbour = 0; neighbour < n; neighbour++) {
            if (neighbour != top && roads[top][neighbour] == 1 && !visited[neighbour]) {
                visited[neighbour] = 1;
                q.push(neighbour);
            }
        }   
    }
}

int findNumOfProvinces(vector<vector<int>>& roads, int n) {
    vector<int> visited(n, 0);

    int count = 0;
    
    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            bfs(vertex, n, roads, visited);
            count++;
        }
    }

    return count;
}