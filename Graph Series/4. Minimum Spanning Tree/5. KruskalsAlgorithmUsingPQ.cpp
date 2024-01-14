#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O((E + V) * Log V)
// Space Complexity: O(V)

struct Edge {
    int weight;
    int first;
    int second;
};

struct compare {
    bool operator()(const Edge &e1, const Edge &e2) {
        return e1.weight > e2.weight;
    }
};

int findUltimateParent(int vertex, vector<int> &parent) {
    int curr = vertex;

    while (curr != parent[curr]) {
        curr = parent[curr];
    }

    return parent[vertex] = curr;
}

int kruskalMST1(int n, vector<vector<int>> &edges) {
    vector<int> parent(n + 1);

    for (int vertex = 0; vertex <= n; vertex++) {
        parent[vertex] = vertex;
    }

    priority_queue<Edge, vector<Edge>, compare> pq;

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        pq.push({weight, first, second});
    } 

    int count = 1; int mstWeight = 0;

    while (count <= n - 1) {
        auto top = pq.top();
        pq.pop();

        int tFirst = top.first;
        int tSecond = top.second;
        int tWeight = top.weight;

        int parent1 = findUltimateParent(tFirst, parent);
        int parent2 = findUltimateParent(tSecond, parent);

        if (parent1 != parent2) {
            count++;
            mstWeight = mstWeight + tWeight;
            parent[parent1] = parent[parent2];
        }
    }

    return mstWeight;
}

vector<Edge> kruskalMST2(int n, vector<vector<int>> &edges) {
    vector<int> parent(n + 1);

    vector<Edge> mst;

    for (int vertex = 0; vertex <= n; vertex++) {
        parent[vertex] = vertex;
    }

    priority_queue<Edge, vector<Edge>, compare> pq;

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        pq.push({weight, first, second});
    } 

    int count = 1; int mstWeight = 0;

    while (count <= n - 1) {
        auto top = pq.top();
        pq.pop();

        int tFirst = top.first;
        int tSecond = top.second;
        int tWeight = top.weight;

        int parent1 = findUltimateParent(tFirst, parent);
        int parent2 = findUltimateParent(tSecond, parent);

        if (parent1 != parent2) {
            count++;
            mstWeight = mstWeight + tWeight;

            mst.push_back({tFirst, tSecond, tWeight});

            parent[parent1] = parent[parent2];
        }
    }

    return mst;
}