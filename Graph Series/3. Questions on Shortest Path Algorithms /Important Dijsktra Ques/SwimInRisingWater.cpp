#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isSafe(int row, int col, int n) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    vector<vector<int>> minTime(n, vector<int>(n, 1e9));
    minTime[0][0] = grid[0][0];

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    pq.push({grid[0][0], {0, 0}});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int time = top.first;
        int row = top.second.first;
        int col = top.second.second;

        for (int i=0; i<4; i++) {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            if (isSafe(newRow, newCol, n) == true) {
                int currMinTime = max(grid[newRow][newCol], time);

                if (currMinTime < minTime[newRow][newCol]) {
                    minTime[newRow][newCol] = currMinTime;

                    if (newRow == n - 1 && newCol == n - 1) {
                        return minTime[n - 1][n - 1];
                    }

                    pq.push({minTime[newRow][newCol], {newRow, newCol}});
                }

/*
                if (grid[newRow][newCol] > time && grid[newRow][newCol] < minTime[newRow][newCol]) {
                    minTime[newRow][newCol] = grid[newRow][newCol];
                    if (newRow == n - 1 && newCol == n - 1) {
                        return minTime[n - 1][n - 1];
                    }
                    pq.push({minTime[newRow][newCol], {newRow, newCol}});
                }
                else if (grid[newRow][newCol] < time && time < minTime[newRow][newCol]) {
                    minTime[newRow][newCol] = time;
                    
                    if (newRow == n - 1 && newCol == n - 1) {
                        return minTime[n - 1][n - 1];
                    }

                    pq.push({minTime[newRow][newCol], {newRow, newCol}});
                }
*/
            }
        }
    }

    return -1;
}