#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int vertex, int trigger, vector<int> &visited, vector<vector<int>> &graph, stack<int> &s) {
    visited[vertex] = 1;
    
    for (int &neighbour : graph[vertex]) {
        if (!visited[neighbour]) {
            dfs(neighbour, trigger, visited, graph, s);
        }
    }
    
    if (trigger == 1) {
        s.push(vertex);
    }
}

int kosaraju(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];

        graph[first].push_back(second);
    }

    stack<int> s;
    
    vector<int> visited(n, 0);
    
    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfs(vertex, 1, visited, graph, s);
        }
    }
    
    vector<vector<int>> newGraph(n);
    
    for (int vertex = 0; vertex < n; vertex++) {
        visited[vertex] = 0;
        for (int &neighbour : graph[vertex]) {
            newGraph[neighbour].push_back(vertex);
        }
    }
    
    int count = 0;
    
    while (!s.empty()) {
        int vertex = s.top();
        s.pop();
        
        if (!visited[vertex]) {
            dfs(vertex, 0, visited, newGraph, s);
            count++;
        }
    }
    
    return count;
}