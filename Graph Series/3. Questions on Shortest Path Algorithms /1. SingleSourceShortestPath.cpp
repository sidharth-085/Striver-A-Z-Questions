#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(V + E)
// Space Complexity: O(V)

// In this question, we find the shortest distance from given source vertex
// to every vertex in undirected unit distance graph. We take the path
// which stores the shortest distance from source to current ith vertex in
// path. So, we do the bfs and check for minimum distance comes out of queue.
// And, finally returns the path vector.

vector<int> shortestPath(int n, vector<vector<int>>&edges, int src) {
    vector<vector<int>> graph(n);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    vector<int> path(n, 1e9);
    path[src] = 0;

    vector<int> visited(n, 0);
    visited[src] = 1;

    queue<pair<int, int>> q;
    q.push({src, 0});

    while (!q.empty()) {
        pair<int, int> top = q.front();
        q.pop();

        int tVertex = top.first;
        int tDist = top.second;

        path[tVertex] = min(path[tVertex], tDist);

        for (int neighbour : graph[tVertex]) {
            if (!visited[neighbour]) {
                visited[neighbour] = 1;
                q.push({neighbour, tDist + 1});
            }
        }
    }

    for (int vertex = 0; vertex < n; vertex++) {
        if (path[vertex] == 1e9) {
            path[vertex] = -1;
        }
    }

    return path;
}