#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(V + E)
// Space Complexity: O(V)

// We can detect the cycle in Directed Graph using Topo Sort because Topo Sort
// is only applicable in the case of DAG. So if there is a cycle in Graph, we
// will not get all the vertices in Topo sort. Hence, we can count the topo 
// sort vertices. If count and n are equal, then there is no cycle and graph
// is DAG. And, if count and n are not equal, hence there is a cycle.

int detectCycleInDirectedGraph(int n, vector<pair<int, int>> &edges) {
    vector<vector<int>> graph(n);

    vector<int> inDegree(n, 0);

    for (auto edge : edges) {
        int first = edge.first - 1;
        int second = edge.second - 1;

        graph[first].push_back(second);
        inDegree[second]++;
    }

    queue<int> q;

    int count = 0;

    for (int vertex = 0; vertex < n; vertex++) {
        if (inDegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        count++;

        for (int neighbour : graph[top]) {
            inDegree[neighbour]--;

            if (inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    if (count == n) {
        return false;
    }

    return true;
}