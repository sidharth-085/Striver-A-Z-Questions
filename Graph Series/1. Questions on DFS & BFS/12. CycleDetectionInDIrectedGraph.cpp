#include <iostream>
#include <vector>
using namespace std;

// Approach : DFS Method
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Here, we use the trick of using Path Visited array, when we are visiting a
// path of directed graph we mark the node as visited and when we backtrack 
// we mark them notPathVisited because we can come back with same path again 
// for detecting cycle. And, when we get the pathVisited and visited both 1,
// means this node is already visited and with same path not other path because
// when we are going back from any path, mark as notPathVisited.

bool dfs(int startVertex, vector<int> &visited, vector<int> &pathVisited, vector<vector<int>> &graph) {
    visited[startVertex] = 1;
    pathVisited[startVertex] = 1;

    for (int neighbour : graph[startVertex]) {
        if (visited[neighbour] == 1 && pathVisited[neighbour] == 1) {
            return true;
        }

        if (visited[neighbour] == 0) {
            if (dfs(neighbour, visited, pathVisited, graph) == true) {
                return true;
            }
        }
    }

    pathVisited[startVertex] = 0;

    return false;
}

bool isCyclic(vector<vector<int>>& edges, int n, int e) {
	vector<vector<int>> graph(n);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
    }

    vector<int> visited(n, 0);
    vector<int> pathVisited(n, 0);

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            if (dfs(vertex, visited, pathVisited, graph) == true) {
                return true;
            }
        }
    }

    return false;
}
