#include <iostream>
#include <vector>
using namespace std;

// Topo Sort is only applicable in Directed Acyclic Graph (DAG), and Topo Sort
// is defined as the linear ordering in which if there is an edge between u and
// v, u always appear before v.

// Time Complexity: O(V + E)
// Space Complexity: O(V)

void topoSortUsingDFS(int startVertex, vector<vector<int>> &graph, vector<int> &visited, vector<int> &topoSort) {
    visited[startVertex] = 1;

    for (int neighbour : graph[startVertex]) {
        if (!visited[neighbour]) {
            topoSortUsingDFS(neighbour, graph, visited, topoSort);
        }
    }

    topoSort.push_back(startVertex);
}

vector<int> topologicalSort(vector<vector<int>> &edges, int e, int n) {
    vector<vector<int>> graph(n);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
    }

    vector<int> visited(n, 0);
    vector<int> topoSort;

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            topoSortUsingDFS(vertex, graph, visited, topoSort);
        }
    }

    reverse(topoSort.begin(), topoSort.end());

    return topoSort;
}