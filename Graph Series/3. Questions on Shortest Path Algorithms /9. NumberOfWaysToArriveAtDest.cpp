#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Time Complexity: O(E Log V)
// Space Complexity: O(V)

// In this question, we have to find the number of paths to reach at dest
// from src. So, it is some kind of DP problem, so we follow the same 
// approach. We do the same Dijkstra Algorithm, and whenever we get the 
// tDist + dist < path[neighbour], we update the path[neighbour]. Also, we 
// push inside the priority queue. And, most importantly, the number of 
// paths to reach at tVertex from src are the same number of path to reach
// at neighbour from src because we are getting the smaller distance path
// via tVertex to neighbour. And, when we get the same distance to reach
// from src to neighbour i.e. tDist + dist == path[neighbour], it means
// we can reach at neighbour via other path with same shortest distance. 
// It means, we have to add the number of paths of new path to old paths
// i.e. numPath[neighbour] + numPath[tVertex].

int numberOfPaths(int src, int dest, int n, vector<vector<pair<int, int>>> &graph) {
    int mod = 1e9 + 7;
    
    vector<long long> path(n, 1e15);
    path[src] = 0;

    vector<long long> numPath(n, 0);
    numPath[src] = 1;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({0, src});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int tVertex = top.second;
        long long tDist = top.first;

        for (auto it : graph[tVertex]) {
            int neighbour = it.first;
            int dist = it.second;

            if (tDist + dist < path[neighbour]) {
                path[neighbour] = tDist + dist;

                pq.push({path[neighbour], neighbour});
                
                numPath[neighbour] = (numPath[tVertex] % mod);
            }
            else if (tDist + dist == path[neighbour]) {
                numPath[neighbour] = (numPath[neighbour] + numPath[tVertex]) % mod;
            }
        }
    }

    return (numPath[dest]) % mod;
}

int countPaths(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto road : roads) {
        int first = road[0];
        int second = road[1];
        int dist = road[2];

        graph[first].push_back({second, dist});
        graph[second].push_back({first, dist});
    }

    return numberOfPaths(0, n - 1, n, graph);
}