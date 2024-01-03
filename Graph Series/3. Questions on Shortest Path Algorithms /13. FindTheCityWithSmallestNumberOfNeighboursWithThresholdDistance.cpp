#include <iostream>
#include <vector>
using namespace std;

// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N)

// In this question, we have to find the city from which if there is path
// starting from it covers least number cities and path distance should
// be under distanceThreshold. Now, firstly we will perform Floyd Warshall
// it will provide us the shortest distance from every vertex to other 
// vertex. Now, we check that for every vertex, if there is distance
// from vertex to neighbour via some path is under distanceThreshold, we
// increment cities[vertex]. And, finally we choose the vertex having min
// cities[vertex] value and return that vertex.

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> graph(n, vector<int>(n, 1e9));

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        graph[first][second] = weight;
        graph[second][first] = weight;
    }

    for (int vertex = 0; vertex < n; vertex++) {
        graph[vertex][vertex] = 0;
    }

    for (int via = 0; via < n; via++) {
        for (int vertex = 0; vertex < n; vertex++) {
            for (int neighbour = 0; neighbour < n; neighbour++) {
                if (vertex == neighbour && graph[vertex][via] == 1e9 || graph[via][neighbour] == 1e9) {
                    continue;
                }

                if (graph[vertex][via] + graph[via][neighbour] < graph[vertex][neighbour]) {
                    graph[vertex][neighbour] = graph[vertex][via] + graph[via][neighbour];
                }
            }
        }
    }

    vector<int> cities(n, 0);

    for (int vertex = 0; vertex < n; vertex++) {
        for (int neighbour = 0; neighbour < n; neighbour++) {
            if (vertex != neighbour && graph[vertex][neighbour] <= distanceThreshold) { 
                cities[vertex]++;
            }
        }
    }

    int mini = 1e9; int ans = -1;

    for (int vertex = 0; vertex < n; vertex++) {
        if (mini >= cities[vertex]) {
            mini = cities[vertex];
            ans = vertex;
        }
    }

    return ans;
}