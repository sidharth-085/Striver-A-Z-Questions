#include <iostream>
#include <vector>
using namespace std;

// Approach: DFS Method 
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Bipartite graph is a graph in which we can color the whole graph using only
// 2 colors. Here, we used the colors array in the place of visited array.
// If the vertex is marked with color 0, neighbour should mark with color 1 and
// vice versa. If we found the neighbour having same color as its parent vertex,
// it is not Bipartite Graph, we return false.

bool dfs(int startVertex, vector<vector<int>>& graph, vector<int> &colors) {
    for (int neighbour : graph[startVertex]) {
        if (colors[neighbour] == colors[startVertex]) {
            return false;
        }
        else if (colors[neighbour] == -1) {
            if (colors[startVertex] == 0) {
                colors[neighbour] = 1;
                if (dfs(neighbour, graph, colors) == false) {
                    return false;
                }
            }
            else {
                colors[neighbour] = 0;
                if (dfs(neighbour, graph, colors) == false) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();

    vector<int> colors(n, -1);

    for (int vertex = 0; vertex < n; vertex++) {
        if (colors[vertex] == -1) {
            colors[vertex] = 0;
            if (dfs(vertex, graph, colors) == false) {
                return false;
            }
        }
    }

    return true;
}