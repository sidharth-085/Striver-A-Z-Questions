#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(N * M * Log (N * M))
// Space Complexity: O(N * M)

// In this question, we have to find the minimum effort to reach from top
// left to bottom right. An Effort is defined as the maximum absolute diff
// between two consecutive cells in the path. So, we have to minimize the
// path effort. To solve this, we use Dijkstra Algorithm in different way.
// Usually, we find the minimum distance to reach at particular cell from
// source, but here we do little different. We store the maximum abs diff
// to reach from source node to that node. 

// This is some kind of Dynamic Programming approach. So, when we get the
// safe cell out of all 4 directions, we take the difference of the heights
// of consecutive cells. And, we compare with previous stored effort, we have
// to take maximum effort in the path so, we store the max of previous cell
// effort and current abs diff. And, compare with current cell effort, we 
// have to take the minimum effort, so consider the minimum out of max 
// effort of that path and current effort, also push in queue. Finally, 
// return the bottom right's cell effort.

int minimumEffortPath(vector<vector<int>>& heights) {
    int n = heights.size();
    int m = heights[0].size();

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    vector<vector<int>> efforts(n, vector<int>(m, 1e9));
    efforts[0][0] = 0;

    // we can use queue here also
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int tRow = top.first;
        int tCol = top.second;

        for (int i=0; i<4; i++) {
            int nRow = tRow + dx[i];
            int nCol = tCol + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m) {
                int absDiff = abs(heights[nRow][nCol] - heights[tRow][tCol]);

                int maxEffort = max(efforts[tRow][tCol], absDiff);

                if (maxEffort < efforts[nRow][nCol]) {
                    efforts[nRow][nCol] = maxEffort;

                    pq.push({nRow, nCol});
                }
            }
        }
    }

    return efforts[n - 1][m - 1];
}