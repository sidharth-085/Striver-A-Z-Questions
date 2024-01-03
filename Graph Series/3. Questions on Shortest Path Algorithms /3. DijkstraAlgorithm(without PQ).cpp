#include <iostream>
#include <vector>
using namespace std;

// Time Complexity: O(V * V * E)
// Space Complexity: O(V)

// In this Dijsktra method, we are not using the Priority Queue. It is
// basically brute force method of Dijsktra method. Below are the steps for 
// this brute force appraoch:

// 1. The approach first find the vertex having minimum distance from source.
// As in the start, we have path array with source marked as 0 because
// we haven't reached any of the vertex till now.

// 2. Then, we get the minimum distance vertex, we mark it visited because
// we dont want to visit that again. Basically, we going to every vertex
// one by one via path array choosing minimum distance vertex and avoiding
// the previous min distance vertex.

// 3. Then, we find again and again the min distance vertex and mark it 
// as visited so that it will not come again. And, now we explore the 
// neighbours of min distance vertex and check if the distance taken to
// reach at min distance vertex + edge distance is less than the distance
// stored in path array, also, current neighbour is not visited. We update
// the distance in path array. Finally, return the array.

int findMinDistanceVertex(vector<int> &path, int n, vector<int> &visited) {
    int minDist = INT_MAX;
    int minVertex = -1;
    
    for (int vertex = 0; vertex < n; vertex++) {
        if (visited[vertex] == 0 && minDist > path[vertex]) {
            minDist = path[vertex];
            minVertex = vertex;
        }
    }

    return minVertex;
}

vector<int> dijkstra(vector<vector<int>> &edges, int n, int e, int src) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int dist = edge[2];

        graph[first].push_back({second, dist});
        graph[second].push_back({first, dist});
    } 
    
    vector<int> path(n, 1e9);
    path[src] = 0;

    vector<int> visited(n, 0);

    for (int i=0; i<n; i++) {
        int minVertex = findMinDistanceVertex(path, n, visited);
        visited[minVertex] = 1;

        for (auto it : graph[minVertex]) {
            int neighbour = it.first;
            int dist = it.second;

            if (visited[neighbour] == 0 && path[minVertex] + dist < path[neighbour]) {
                path[neighbour] = path[minVertex] + dist;
            }
        }
    }

    return path;
}