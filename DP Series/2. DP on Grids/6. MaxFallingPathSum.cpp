#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to find the maximum sum from any element in first row
// to any element in last row. So, here both starting and ending points are variable

// Approach 1: Brute Force Recursive Solution
// Time Complexity: O(M * 3^(N * M))
// Space Complexity: O(N)

// Function to recursively find the maximum path sum starting from a given cell (row, col)
int getMaxSumPath(int row, int col, int n, int m, vector<vector<int>> &grid) {
    // Base case: If the column is out of bounds, return INT_MIN
    if (col < 0 || col >= m) {
        return INT_MIN;
    }
    
    // If we reach the last row, return the value in the grid at this cell
    if (row == n-1) {
        return grid[row][col];
    }

    // Recursive calls to find the maximum path sum by moving down and diagonally
    int down = getMaxSumPath(row + 1, col, n, m, grid); 

    int leftDiag = getMaxSumPath(row + 1, col - 1, n, m, grid);

    int rightDiag = getMaxSumPath(row + 1, col + 1, n, m, grid);

    // Return the maximum of the three possible paths plus the value at the current cell
    return max(down, max(leftDiag, rightDiag)) + grid[row][col];
}

// Function to find the maximum path sum starting from any cell in the top row
int getMaxPathSum(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    int finalMax = INT_MIN;

    // Iterate through each cell in the top row to find the maximum path sum
    for (int i=0; i<m; i++) {
        finalMax = max(finalMax, getMaxSumPath(0, i, n, m, grid));
    }   

    return finalMax;
}

// Approach 2: Memoization Solution
// Time Complexity: O(N * M * M)
// Space Complexity: O(N * M)

// Function to recursively find the maximum path sum starting from a given cell (row, col) with memoization
int getMaxSumPath(int row, int col, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &dp) {
    // Base case: If the column is out of bounds, return INT_MIN
    if (col < 0 || col >= m) {
        return INT_MIN;
    }
    
    // If we reach the last row, return the value in the grid at this cell
    if (row == n-1) {
        return grid[row][col];
    }

    // If the result for this cell has already been calculated, return it
    if (dp[row][col] != INT_MIN) {
        return dp[row][col];
    }

    // Recursive calls to find the maximum path sum by moving down and diagonally
    int down = getMaxSumPath(row + 1, col, n, m, grid, dp);
    int leftDiag = getMaxSumPath(row + 1, col - 1, n, m, grid, dp);
    int rightDiag = getMaxSumPath(row + 1, col + 1, n, m, grid, dp);

    // Store the result in the memoization table and return it
    return dp[row][col] = grid[row][col] + max(down, max(leftDiag, rightDiag));
}

// Function to find the maximum path sum starting from any cell in the top row using memoization
int getMaxPathSum(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Initialize a memoization table with INT_MIN values
    vector<vector<int>> dp(n, vector<int>(m, INT_MIN));

    int finalMax = INT_MIN;

    // Iterate through each cell in the top row to find the maximum path sum
    for (int i = 0; i < m; i++) {
        int currMaxPathSum = getMaxSumPath(0, i, n, m, grid, dp);
        finalMax = max(finalMax, currMaxPathSum);
    }   

    return finalMax;
}

// Approach 3: Tabulation Method (Bottom-Up DP)
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

// Function to find the minimum falling path sum from top to bottom
int minFallingPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    int finalMax = INT_MIN;

    // Initialize a DP table with INT_MIN values
    vector<vector<int>> dp(n, vector<int>(m, INT_MIN));

    // Initialize the last row of the DP table with values from the grid
    for (int col = 0; col < m; col++) {
        dp[n-1][col] = grid[n-1][col]; 
    }

    // Iterate through rows in reverse order and columns from right to left
    for (int row = n-2; row >= 0; row--) {
        for (int col = m-1; col >= 0; col--) {
            // Calculate the minimum falling path sum by considering three possible moves
            
            int down = dp[row + 1][col];
            int leftDiag = INT_MIN;
            int rightDiag = INT_MIN;

            if (col > 0) {
                leftDiag = dp[row + 1][col - 1];
            }

            if (col < m-1) {
                rightDiag = dp[row + 1][col + 1];
            }

            dp[row][col] = min(down, min(leftDiag, rightDiag)) + grid[row][col];
        }
    }

    // Find the maximum value in the first row of the DP table
    for (int i=0; i<m; i++) {
        finalMax = max(finalMax, dp[0][i]);
    }

    return finalMax;
}

// Approach 4: Space Optimization by changing the given grid (Not preferred)
// Time Complexity: O(N * M)
// Space Complexity: O(1)

int getMaxPathSum(vector<vector<int>>& grid) {
    int n = grid.size();

    int m = grid[0].size();

    int finalMax = INT_MIN;

    // Update the given grid to store intermediate results
    for (int row = n-2; row >= 0; row--) {
        for (int col = m-1; col >= 0; col--) {
            int down = grid[row + 1][col];

            int leftDiag = INT_MIN;
            int rightDiag = INT_MIN;

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
        finalMax = min(finalMax, grid[0][i]);
    }

    return finalMax;
}

// Approach 5: Space Optimization (Preferred)
// Time Complexity: O(N * M)
// Space Complexity: O(M)

int getMaxPathSum(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int finalMax = INT_MIN;

    vector<int> nextRow(m, INT_MIN);

    // Initialize the bottom row of the dp table
    for (int col = 0; col < m; col++) {
        nextRow[col] = grid[n-1][col]; 
    }

    // Fill in the dp table from bottom to top
    for (int row = n-2; row >= 0; row--) {
        vector<int> currRow(m, INT_MIN);

        for (int col = m-1; col >= 0; col--) {
            // Calculate the minimum falling path sum for the current cell
            int down = nextRow[col];

            int leftDiag = INT_MIN;
            int rightDiag = INT_MIN;

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
        finalMax = min(finalMax, nextRow[i]);
    }

    return finalMax;
}