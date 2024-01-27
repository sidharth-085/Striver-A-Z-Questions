#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force Recursive Solution
// Time Complexity: O(M * 3^(N * M))
// Space Complexity: O(N)

int getMinSumPath(int row, int col, int n, int m, vector<vector<int>> &grid) {
    if (col < 0 || col >= m) {
        return INT_MAX; // Base case: out of bounds, return a large value
    }
    
    if (row == n-1) {
        return grid[row][col]; // Base case: reached the last row, return the grid value
    }

    // Recursive calls to explore three possible paths
    int down = getMinSumPath(row + 1, col, n, m, grid);

    int leftDiag = getMinSumPath(row + 1, col - 1, n, m, grid);

    int rightDiag = getMinSumPath(row + 1, col + 1, n, m, grid);

    // Return the minimum of the three paths plus the current grid value
    return min(down, min(leftDiag, rightDiag)) + grid[row][col];
}

int getMaxPathSum(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    int finalMin = INT_MAX;

    // Iterate through the first row to find the minimum falling path sum
    for (int i = 0; i < m; i++) {
        finalMin = min(finalMin, getMinSumPath(0, i, n, m, grid));
    }   

    return finalMin;
}

// Approach 2: Memoization Solution
// Time Complexity: O(N * M * M)
// Space Complexity: O(N * M)

int getMinxSumPath(int row, int col, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &dp) {
    if (col < 0 || col >= m) {
        return INT_MAX; // Base case: out of bounds, return a large value
    }
    
    if (row == n-1) {
        return grid[row][col]; // Base case: reached the last row, return the grid value
    }

    if (dp[row][col] != INT_MAX) {
        return dp[row][col]; // If already computed, return the memoized value
    }

    // Recursive calls to explore three possible paths
    int down = getMinxSumPath(row + 1, col, n, m, grid, dp);

    int leftDiag = getMinxSumPath(row + 1, col - 1, n, m, grid, dp);

    int rightDiag = getMinxSumPath(row + 1, col + 1, n, m, grid, dp);

    // Memoize the result and return it
    return dp[row][col] = grid[row][col] + min(down, min(leftDiag, rightDiag));
}

int getMaxPathSum(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, INT_MAX));

    int finalMin = INT_MAX;

    // Iterate through the first row to find the minimum falling path sum
    for (int i = 0; i < m; i++) {
        int currMaxPathSum = getMinxSumPath(0, i, n, m, grid, dp);
        finalMin = min(finalMin, currMaxPathSum);
    }   

    return finalMin;
}

// Approach 3: Tabulation Method (Bottom Up Dp)
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int finalMin = INT_MAX;

    vector<vector<int>> dp(n, vector<int>(m, INT_MAX));

    // Initialize the bottom row of the dp table
    for (int col = 0; col < m; col++) {
        dp[n-1][col] = grid[n-1][col]; 
    }

    // Fill in the dp table from bottom to top
    for (int row = n-2; row >= 0; row--) {
        for (int col = m-1; col >= 0; col--) {
            // Calculate the minimum falling path sum for the current cell

            int down = dp[row + 1][col];
            int leftDiag = INT_MAX;
            int rightDiag = INT_MAX;

            if (col > 0) {
                leftDiag = dp[row + 1][col - 1];
            }

            if (col < m-1) {
                rightDiag = dp[row + 1][col + 1];
            }

            dp[row][col] = min(down, min(leftDiag, rightDiag)) + grid[row][col];
        }
    }

    // Find the minimum falling path sum in the top row of the dp table
    for (int i=0; i<m; i++) {
        finalMin = min(finalMin, dp[0][i]);
    }

    return finalMin;
}

// Approach 4: Space Optimization by changing the given grid (Not preferred)
// Time Complexity: O(N * M)
// Space Complexity: O(1)

int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int finalMin = INT_MAX;

    // Update the given grid to store intermediate results
    for (int row = n-2; row >= 0; row--) {
        for (int col = m-1; col >= 0; col--) {
            int down = grid[row + 1][col];

            int leftDiag = INT_MAX;
            int rightDiag = INT_MAX;

            if (col > 0) {
                leftDiag = grid[row + 1][col - 1];
            }

            if (col < m-1) {
                rightDiag = grid[row + 1][col + 1];
            }

            grid[row][col] = min(down, min(leftDiag, rightDiag)) + grid[row][col];
        }
    }

    // Find the minimum falling path sum in the top row of the updated grid
    for (int i=0; i<m; i++) {
        finalMin = min(finalMin, grid[0][i]);
    }

    return finalMin;
}

// Approach 5: Space Optimization (Preferred)
// Time Complexity: O(N * M)
// Space Complexity: O(M)

int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int finalMin = INT_MAX;

    vector<int> nextRow(m, INT_MAX);

    // Initialize the bottom row of the dp table
    for (int col = 0; col < m; col++) {
        nextRow[col] = grid[n-1][col]; 
    }

    // Fill in the dp table from bottom to top
    for (int row = n-2; row >= 0; row--) {
        vector<int> currRow(m, INT_MAX);

        for (int col = m-1; col >= 0; col--) {
            // Calculate the minimum falling path sum for the current cell
            int down = nextRow[col];

            int leftDiag = INT_MAX;
            int rightDiag = INT_MAX;

            if (col > 0) {
                leftDiag = nextRow[col - 1];
            }
            if (col < m-1) {
                rightDiag = nextRow[col + 1];
            }

            currRow[col] = min(down, min(leftDiag, rightDiag)) + grid[row][col];
        }
        nextRow = currRow;
    }

    // Find the minimum falling path sum in the top row of the dp table
    for (int i=0; i<m; i++) {
        finalMin = min(finalMin, nextRow[i]);
    }

    return finalMin;
}