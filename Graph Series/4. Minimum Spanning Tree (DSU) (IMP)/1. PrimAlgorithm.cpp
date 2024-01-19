#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// In this Algorith of finding MST, we follow just simple steps which are:
// We have to find the shortest weighted edges and mark the vertex as visited.
// For this, we use the min priority queue, which ensures that the edges
// with minimum weights are there. Also, mark them visited when popped out
// from queue. And, skip those vertex which are visited already (popped 
// from queue).

// Time Complexity: O(E * Log V)
// Space Complexity: O(V)

// This code works when we only need sum of minimum spanning tree.

int minimumSpanningTree1(vector<vector<int>>& edges, int n) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        graph[first].push_back({second, weight});
        graph[second].push_back({first, weight});
    }

    vector<int> visited(n, 0);

    int mstSum = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int tWeight = top.first;
        int tVertex = top.second;

        if (visited[tVertex] == 1) {
            continue;
        }

        mstSum = mstSum + tWeight;

        visited[tVertex] = 1;

        for (auto &it : graph[tVertex]) {
            int neighbour = it.first;
            int weight = it.second;

            if (visited[neighbour] == 0) {
                pq.push({weight, neighbour});
            }
        }
    }
    
    return mstSum;
}

// When we need, list of edges which makes Minimum Spanning Tree. We have
// to create a structure to store details together and return as vector
// of Edge which contains the minimum spanning tree edges with weights.

struct Edge {
    int weight;
    int vertex;
    int parent;
};

vector<Edge> minimumSpanningTree2(vector<vector<int>>& edges, int n) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        graph[first].push_back({second, weight});
        graph[second].push_back({first, weight});
    }

    vector<int> visited(n, 0);

    vector<Edge> mst;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({0, 0, -1});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int tWeight = top.weight;
        int tVertex = top.vertex;
        int tParent = top.parent;

        if (visited[tVertex] == 1) {
            continue;
        }

        mst.push_back({tParent, tVertex, tWeight});

        visited[tVertex] = 1;

        for (auto &it : graph[tVertex]) {
            int neighbour = it.first;
            int weight = it.second;

            if (visited[neighbour] == 0) {
                pq.push({weight, neighbour, tVertex});
            }
        }
    }

    return mst;
}