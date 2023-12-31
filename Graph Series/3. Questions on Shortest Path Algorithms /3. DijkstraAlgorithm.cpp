#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(E * Log V)
// Space Complexity: O(V)

// In this algorithm, we find the shortest distance from given source and
// stores in the array. It is faster than BFS, thats why we used this 
// algorithm. But, main point is this algorithm not works for Negative
// edges or negative cycles.

vector<int> dijkstra(vector<vector<int>> &edges, int n, int e, int src) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int dist = edge[2];

        graph[first].push_back({second, dist});
        graph[second].push_back({first, dist});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    vector<int> distance(n, 1e9);
    distance[src] = 0;

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int tVertex = top.second;
        int tDist = top.first;

        for (auto it : graph[tVertex]) {
            int neighbour = it.first;
            int dist = it.second;

            if (tDist + dist < distance[neighbour]) {
                distance[neighbour] = tDist + dist;

                pq.push({distance[neighbour], neighbour});
            }
        }
    }

    return distance;
}