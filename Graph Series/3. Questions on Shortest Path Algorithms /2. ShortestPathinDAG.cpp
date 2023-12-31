#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Time Complexity: O(V + E + (N*E))
// Space Complexity: O(V)

// In this question, we have to find the shortest path in DAG. The general
// method of BFS, we cant follow here due to Directed Graph. So, we follow
// the Topo sort approach.
// Firstly, we find the topo sort of the given graph and then, remove every
// vertex from stack. And, for every vertex there are some neighbours, select
// the minimum distance by adding the current dist with that vertex distance.
// And, minimize the dist for every vertex. Finally return the path vector.

void topoSort(int startVertex, vector<vector<pair<int, int>>> &graph, vector<int> &visited, stack<int> &stk) {
    visited[startVertex] = 1;

    for (auto it : graph[startVertex]) {
        int neighbour = it.first;
        int dist = it.second;

        if (!visited[neighbour]) {
            topoSort(neighbour, graph, visited, stk);
        }
    }

    stk.push(startVertex);
}

vector<int> shortestPath(int src, int n, vector<vector<pair<int, int>>> &graph, stack<int> &stk) {
    vector<int> path(n, 1e9);
    path[src] = 0;

    while (!stk.empty()) {
        int tVertex = stk.top();
        stk.pop();

        for (auto it : graph[tVertex]) {
            int neighbour = it.first;
            int dist = it.second;

            int currDist = path[tVertex] + dist;

            path[neighbour] = min(path[neighbour], currDist);
        }
    }

    for (int vertex = 0; vertex < n; vertex++) {
        if (path[vertex] == 1e9) {
            path[vertex] = -1;
        }
    }

    return path;
}
 
vector<int> shortestPathInDAG(int n, int m, vector<vector<int>> &edges) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        graph[first].push_back({second, weight});
    }

    vector<int> visited(n, 0);

    stack<int> stk;

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            topoSort(vertex, graph, visited, stk);
        }
    } 

    return shortestPath(0, n, graph, stk);
}
