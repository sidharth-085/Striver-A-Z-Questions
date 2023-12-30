#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Time Complexity: O(V + E)
// Space Complexity: O(V)

// In this question, we have to find the safe states (there are those vertices
// who have all the paths ending at terminal node starting from them). So, 
// what we do is, we apply the Cycle Detection Method in Directed Graph here.
// Hence, when we get the cycle it means, it will be not be safe state because
// the path in any cycle will not ends at terminal node. So, when keep an array
// check, which stores the safe nodes as value 1. So, when we call dfs same as
// cycle detection method, if we get cycle we will mark that as 0 in check. 
// At last, only take those who have value in check as 1 and sort them.

bool dfs(int startVertex, vector<vector<int>> &graph, vector<int> &visited, vector<int> &pathVisited, vector<int> &check) {
    visited[startVertex] = 1;

    pathVisited[startVertex] = 1;

    for (int neighbour : graph[startVertex]) {
        if (visited[neighbour] == 1 && pathVisited[neighbour] == 1) {
            check[startVertex] = 0;
            return true;
        }

        if (!visited[neighbour]) {
            if (dfs(neighbour, graph, visited, pathVisited, check) == true) {
                check[startVertex] = 0;
                return true;
            }
        }
    }

    pathVisited[startVertex] = 0;
    check[startVertex] = 1;

    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<int> safeNodes;

    vector<int> visited(n, 0);
    vector<int> pathVisited(n, 0);
    vector<int> check(n, 0);

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfs(vertex, graph, visited, pathVisited, check);
        }
    }

    for (int vertex = 0; vertex < n; vertex++) {
        if (check[vertex] == 1) {
            safeNodes.push_back(vertex);
        }
    }

    sort(safeNodes.begin(), safeNodes.end());

    return safeNodes;
}