#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

void dfs(int vertex, int parent, int &timer, vector<int> &visited, vector<int> &disc, vector<int> &low, vector<vector<int>> &graph, vector<vector<int>> &criticalConnections) {
    visited[vertex] = 1;

    disc[vertex] = timer;
    low[vertex] = timer;

    timer++;

    for (int &neighbour : graph[vertex]) {
        if (neighbour == parent) {
            continue;
        }

        if (visited[neighbour] == 0) {
            dfs(neighbour, vertex, timer, visited, disc, low, graph, criticalConnections);
            low[vertex] = min(low[vertex], low[neighbour]);

            if (low[neighbour] > disc[vertex]) {
                criticalConnections.push_back({vertex, neighbour});
            }

        }
        else {
            low[vertex] = min(low[vertex], low[neighbour]);
        }
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);

    for (auto &connection : connections) {
        int first = connection[0];
        int second = connection[1];

        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    vector<int> visited(n, 0);

    vector<int> disc(n);
    vector<int> low(n);

    int timer = 0;

    vector<vector<int>> criticalConnections;

    for (int vertex = 0; vertex < n; vertex++) {
        if (visited[vertex] == 0) {
            dfs(vertex, -1, timer, visited, disc, low, graph, criticalConnections);
        } 
    }

    return criticalConnections;
}