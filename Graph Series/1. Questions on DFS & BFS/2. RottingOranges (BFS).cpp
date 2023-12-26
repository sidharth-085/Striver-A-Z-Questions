#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Approach 1: BFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Steps: 
// 1. First take the rotton nodes (marked with 2) in the queue & take the number of rotton nodes.
// 2. Do the BFS with while loop, take the maximum time for every rotton node inside the queue.
// 3. Insert the node inside the queue with its current time when it is fresh node && not visited before.

// We can do it without using the visited array, but we have to alter the given data for it.

int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> visited(n, vector<int>(m, 0));

    queue<pair<pair<int, int>, int>> q;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int freshCount = 0;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 2) {
                q.push({{row, col}, 0});
                visited[row][col] = 1;
            }
            else if (grid[row][col] == 1) {
                freshCount++;
            }
        }
    }

    int time = 0;
    int count = 0;

    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        int tRow = top.first.first;
        int tCol = top.first.second;
        int tTime = top.second;

        time = max(time, tTime);

        for (int i=0; i<4; i++) {
            int nRow = tRow + dx[i];
            int nCol = tCol + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && grid[nRow][nCol] == 1 && visited[nRow][nCol] == 0) {
                visited[nRow][nCol] = 1;

                q.push({{nRow, nCol}, tTime + 1});
                
                count++;
            }
        }
    }

    if (count != freshCount) {
        return -1;
    }

    return time;
}