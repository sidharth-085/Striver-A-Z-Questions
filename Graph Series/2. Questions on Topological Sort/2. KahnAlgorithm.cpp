#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Kahn's Algorithm is basically BFS version of Topo Sort. In this method, we
// are using the new technique which is inDegree. We all know, if there is 
// DAG there is always atleast one vertex having inDegree as 0. So, we push 
// them inside the queue, and reduce the inDegree of the neighbours one by one. 
// If the neighbour, inDegree becomes 0, we push again in queue. Also, when we
// pop out front vertex from queue, we push it inside the topoSort vector.

vector<int> topologicalSort(vector<vector<int>> &edges, int e, int n) {
    vector<vector<int>> graph(n);

    vector<int> inDegree(n, 0);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
        inDegree[second]++;
    }

    queue<int> q;

    vector<int> topoSort;

    for (int vertex = 0; vertex < n; vertex++) {
        if (inDegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        topoSort.push_back(top);

        for (int neighbour : graph[top]) {
            inDegree[neighbour]--;

            if (inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    return topoSort;
}
