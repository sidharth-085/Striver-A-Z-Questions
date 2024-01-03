#include <iostream>
#include <vector>
using namespace std;

// Time Complexity: O(V * E)
// Space Complexity: O(V)

// In the Bellman Ford Algorithm, we relax all the edges (n - 1) times
// sequentially. Relaxing the edges means, every edge contains start, end
// and distance between start and end. So, checking that path[start] + dist
// is less than path[end], if yes we update the path[end] with lesser distance.
// This is we call the relaxing the edges. And, finally return the path 
// array.

// This algorithm can also detect negative cycles. As we know, if there is
// negative cycle, the distance between the cycle will always be reducing.
// And, in Bellman Ford we relax the edges (n - 1) times. But, if we relax
// the edges one more time i.e. nth time, if the distance is still reducing 
// it means there is negative cycle.

vector<int> bellmonFord(int n, int m, int src, vector<vector<int>> &edges) {
    // if vertex are from 0 to n - 1.
    vector<int> path(n, 1e9);
    path[src] = 0;

    int count = n - 1;

    // relaxing the edges (n - 1) times

    while (count--) {
        for (auto &edge : edges) {
            int start = edge[0];
            int end = edge[1];
            int dist = edge[2];

            if (path[start] + dist < path[end]) {
                path[end] = path[start] + dist;
            }
        }
    }

    // nth time relaxing the edges

    for (auto &edge : edges) {
        int start = edge[0];
        int end = edge[1];
        int dist = edge[2];

        if (path[start] + dist < path[end]) {
            return {};
            // this means it contains negative cycle, so we return empty
            // array.
        }
    }

    return path;
}