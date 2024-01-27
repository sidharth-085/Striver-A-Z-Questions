#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Solution
// Time Complexity: O(2^(N * M)) - Exponential
// Space Complexity: O(N * M) - Recursive Stack

int minSumPathHelper(int row, int col, vector<vector<int>> &grid) {
    if (row == 0 && col == 0) {
        return grid[0][0];
    }

    if (row < 0 || col < 0) {
        return INT_MAX;
    }

    // Recursively calculate the minimum path sum by considering the right and down movements.
    int right = minSumPathHelper(row, col - 1, grid);
    int down = minSumPathHelper(row - 1, col, grid);

    // Return the minimum of right and down plus the current cell's value.
    return min(right, down) + grid[row][col];
}

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    return minSumPathHelper(n-1, m-1, grid);
}

// Approach 2: Memoization Solution
// Time Complexity: O(N * M) - Linear
// Space Complexity: O(N * M) - Memoization Table

int minSumPathHelper(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &dp) {
    if (row == 0 && col == 0) {
        return grid[0][0];
    }

    if (row < 0 || col < 0) {
        return INT_MAX;
    }

    // If the value is already computed and stored in the memoization table, return it.
    if (dp[row][col] != -1) {
        return dp[row][col];
    }

    // Calculate the minimum path sum by considering the right and down movements.
    int right = minSumPathHelper(row, col - 1, grid, dp);
    int down = minSumPathHelper(row - 1, col, grid, dp);

    // Store the result in the memoization table and return it.
    return dp[row][col] = min(right, down) + grid[row][col];
}

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Create a memoization table with initial values set to -1.
    vector<vector<int>> dp(n, vector<int>(m, -1));
    
    return minSumPathHelper(n-1, m-1, grid, dp);
}

// Approach 3: Iterative DP Solution
// Time Complexity: O(N * M) - Linear
// Space Complexity: O(N * M) - DP Table

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Create a DP table to store minimum path sums.
    vector<vector<int>> dp(n, vector<int>(m, INT_MAX));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (row == 0 && col == 0) {
                dp[row][col] = grid[row][col];
            }
            else {
                int right = INT_MAX;
                int down = INT_MAX;

                // Calculate the minimum path sum by considering the right and down movements.
                if (col > 0) {
                    right = dp[row][col - 1];
                }

                if (row > 0) {
                    down = dp[row - 1][col];
                }

                // Update the DP table with the minimum sum for the current cell.
                dp[row][col] = min(right, down) + grid[row][col];
            }
        }
    }

    // The last cell of the DP table contains the minimum path sum.
    return dp[n-1][m-1];
}

// Approach 4: Space Optimization
// Time Complexity: O(N * M) - Linear
// Space Complexity: O(N) - Current and Previous Rows

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Create vectors to store the current and previous rows' minimum path sums.
    vector<int> prevRow(m, 0);

    for (int row = 0; row < n; row++) {
        vector<int> currRow(m, 0);

        for (int col = 0; col < m; col++) {
            if (row == 0 && col == 0) {
                currRow[col] = grid[row][col];
            }
            else {
                int right = INT_MAX;
                int down = INT_MAX;

                // Calculate the minimum path sum by considering the right and down movements.
                if (col > 0) {
                    right = currRow[col - 1];
                }

                if (row > 0) {
                    down = prevRow[col];
                }

                // Update the current row with the minimum sum for the current cell.
                currRow[col] = min(right, down) + grid[row][col];
            }
        }

        // Update the previous row with the current row for the next iteration.
        prevRow = currRow;
    }

    // The last element of the previous row contains the minimum path sum.
    return prevRow[m-1];
}