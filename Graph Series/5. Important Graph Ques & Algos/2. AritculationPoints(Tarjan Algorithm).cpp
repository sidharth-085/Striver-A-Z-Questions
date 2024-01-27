#include <iostream>
#include <vector>
#include <set>
using namespace std;

void dfs(int vertex, int parent, int &timer, vector<int> &visited, vector<int> &disc, vector<int> &low, vector<vector<int>> &graph, set<int> &st) {
    visited[vertex] = 1;

    disc[vertex] = timer;
    low[vertex] = timer;

    timer++;

    int child = 0;

    for (int &neighbour : graph[vertex]) {
        if (neighbour == parent) {
            continue;
        }

        if (visited[neighbour] == 0) {
            dfs(neighbour, vertex, timer, visited, disc, low, graph, st);

            low[vertex] = min(low[vertex], low[neighbour]);

            if (parent != -1 && low[neighbour] >= disc[vertex]) {
                st.insert(vertex);
            }

            child++;
        }
        else {
            low[vertex] = min(low[vertex], disc[neighbour]);
        }
    }

    if (parent == -1 && child > 1) {
        st.insert(vertex);
    }
}

vector<int> articulationPoints(vector<vector<int>> &edges, int n) {
    vector<vector<int>> graph(n + 1);

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
        graph[second].push_back(first);
    } 

    vector<int> visited(n + 1, 0);
    vector<int> disc(n + 1);
    vector<int> low(n + 1);

    set<int> st;

    int timer = 0;

    for (int vertex = 1; vertex <= n; vertex++) {
        if (visited[vertex] == 0) {
            dfs(vertex, -1, timer, visited, disc, low, graph, st);
        }
    }

    vector<int> ans;

    for (auto &point : st) {
        ans.push_back(point);
    }

    return ans;
}