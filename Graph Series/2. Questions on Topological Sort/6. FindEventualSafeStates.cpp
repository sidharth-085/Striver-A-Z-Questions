#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(V + E)
// Space Complexity: O(V)

// This question is same as DFS section. But, it can also be solved using Topo
// sort method (Kahn's Algorithm). Firstly, we reverse the edges so that, we can
// apply Kahn's Algorithm (outDegree becomes inDegree), So, when we call kahn's 
// algorithm, it basically, decreases the inDegree of new graph one by one, and
// when we got the inDegree as 0 for any neighbour, we push it inside queue.
// But, when there is cycle, it is always have one inDegree due to cycle. 
// So, it will not count in safe states. 

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<int> safeNodes;

    vector<vector<int>> newGraph(n);

    vector<int> inDegree(n, 0);

    for (int vertex = 0; vertex < n; vertex++) {
        for (int neighbour : graph[vertex]) {
            newGraph[neighbour].push_back(vertex);

            inDegree[vertex]++;
        }
    }

    queue<int> q;

    for (int vertex = 0; vertex < n; vertex++) {
        if (inDegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        for (int neighbour : newGraph[top]) {
            inDegree[neighbour]--;

            if (inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }

        safeNodes.push_back(top);
    }

    sort(safeNodes.begin(), safeNodes.end());

    return safeNodes;
}