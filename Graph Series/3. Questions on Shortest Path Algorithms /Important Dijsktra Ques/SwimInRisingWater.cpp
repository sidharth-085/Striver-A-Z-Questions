#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// In this question, we have to find the minimum time to so that the
// person starting at (0, 0) can reach to (n - 1, n - 1) in minimum
// time. And given that, the value of the cell which is also depth 
// of the cell and time is same 't'. So, for reaching at any cell
// it takes 't' time, but if the current cell value is more than 
// adjacent value, there is not time addition it can swim if adjacent
// cell value is small. 

// This example is best case for Dijsktra Algorithm applied in grid
// with weights. 

// So, we can do this question with Dijsktra Algorithm in 3 steps:

// 1. Firstly, we have to create minTime grid which denotes minimum
// time to reach at a particular cell. Now, we mark minTime[0][0] as
// grid[0][0] value because if first value of grid is non zero, it 
// means even to start from cell 0, we have to wait grid[0][0] time.
// Therefore, we have to start from grid[0][0] value to taken into 
// account. Now, for Dijsktra we use priority queue which takes 
// cells value and row & col pairs and add to the pq. 

// 2. Now, we take out every element of the priority queue and get
// the time, row and col values. Here, 'time' denotes to the time
// required to reach at (row, col) destination. It is not minTime[row][col].
// So, now when we are standing at (row, col) cell we check all 4 
// directions. If the value of adjacent cell is smaller than 'time'
// which denotes the current time taken to reach at (row, col), we 
// can move to adjacent cell without taking more time so, now we
// just have to compare is 'time' is less than minTime[newRow][newCol]
// or not and if it is, update minTime[newRow][minCol]. Another case
// can be there, which is if value of adjacent cell grid[newRow][newCol] 
// is more than 'time', then we have to check is grid[newRow][newCol] 
// is less than minTime[newRow][newCol] or not, if it is, update 
// minTime[newRow][newCol].

// 3. Lastly, if any of the case is true, then just add the corresponding
// value of updated minTime and newRow and newCol to pq and run till
// pq becomes empty. Finally, return the value minTime[n - 1][n - 1].

// Time Complexity: (N * N * Log (N * N))
// Space Complexity: O(N * N)

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