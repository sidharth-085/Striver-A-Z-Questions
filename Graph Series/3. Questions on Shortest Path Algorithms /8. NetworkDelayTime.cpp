#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Time Complexity: O(E Log V)
// Space Complexity: O(V)

// In this question, we have to find the minimum time in which src can
// reach out to all nodes. Therefore, we have to calculate the shortest 
// time from src to all nodes. And, the maximum time to reach at a node 
// from src, will be the minimum time to reach all nodes.

int networkDelayTime(vector<vector<int>>& times, int n, int src) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto time : times) {
        int first = time[0] - 1;
        int second = time[1] - 1;
        int dist = time[2];

        graph[first].push_back({second, dist});
    }

    vector<int> path(n, 1e9);
    path[src - 1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src - 1});

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int tVertex = top.second;
        int tDist = top.first;

        for (auto it : graph[tVertex]) {
            int neighbour = it.first;
            int dist = it.second;

            if (tDist + dist < path[neighbour]) {
                path[neighbour] = tDist + dist;
                pq.push({path[neighbour], neighbour});
            }
        }
    }

    int time = INT_MIN;

    for (int vertex = 0; vertex < n; vertex++) {
        if (path[vertex] == 1e9) {
            return -1;
        }

        time = max(time, path[vertex]);
    }

    return time;
}