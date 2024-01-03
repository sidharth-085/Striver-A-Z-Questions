#include <iostream>
#include <vector>
using namespace std;

// Time Complexity: O(V * V * V)
// Space Complexity: O(V * V)

// In the Floyd Warshall Algorithm, basically this algorithm is different
// than Bellman Ford and Dijsktra Algorithm. It uses the adjacency matrix.
// And, it involves higher space and time complexity because it finds the
// shortest distance from every vertex to every vertex. 

// In this algorithm, we follow the approach of checking the path via a
// particular vertex. It means we check that distance to reach from a to b
// via c, i.e. graph[a][c] + graph[c][b]. If it is less than graph[a][b], we
// update it with smaller one. And, we take via path with every vertex.
// This is Floyd Warshall Algorithm.

int floydWarshall(int n, int m, int src, int dest, vector<vector<int>> &edges) {
    vector<vector<int>> graph(n, vector<int>(n, 1e9));

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        graph[first][second] = weight;
    }

    for (int vertex = 0; vertex < n; vertex++) {
        graph[vertex][vertex] = 0;
    }

    for (int via = 0; via < n; via++) {
        for (int vertex = 0; vertex < n; vertex++) {
            for (int neighbour = 0; neighbour < n; neighbour++) {
                if ((vertex == neighbour) && (graph[vertex][via] == 1e9 || graph[via][neighbour] == 1e9)) {
                    continue;
                }

                if (graph[vertex][via] + graph[via][neighbour] < graph[vertex][neighbour]) {
                    graph[vertex][neighbour] = graph[vertex][via] + graph[via][neighbour];
                }
            }
        }
    }

    return graph[src][dest];
}