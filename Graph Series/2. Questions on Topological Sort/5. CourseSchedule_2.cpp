#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Here, just we have to find the topoSort, if size of topoSort vector is 
// same as numCourses, we return topoSort. But, if they are not equal we have
// to return empty array.

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);

    vector<int> inDegree(numCourses, 0);

    for (auto edge : prerequisites) {
        int first = edge[0];
        int second = edge[1];

        graph[second].push_back(first);
        inDegree[first]++;
    }

    queue<int> q;

    vector<int> topoSort;

    for (int vertex = 0; vertex < numCourses; vertex++) {
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

    if (topoSort.size() == numCourses) {
        return topoSort;
    }

    return {};
}