#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N * M))
// Space Complexity: O(N + M)

int uniquePathsHelper(int row, int col, vector<vector<int>> &obstacleGrid) {
    // If we encounter an obstacle at this cell, return 0
    if (row >= 0 && col >= 0 && obstacleGrid[row][col] == 1) {
        return 0;
    }

    // If we reach the top-left cell, we've found a valid path
    if (row == 0 && col == 0) {
        return 1;
    } 

    // If we go out of bounds, return 0
    if (row < 0 || col < 0) {
        return 0;
    }

    // Calculate the number of paths by moving right and down
    int right = uniquePathsHelper(row, col - 1, obstacleGrid);
    int down = uniquePathsHelper(row - 1, col, obstacleGrid);

    // Return the sum of paths going right and down
    return right + down;
}

// Main function for Approach 1
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size();
    int m = obstacleGrid[0].size();

    // Start the recursive calculation from the bottom-right cell
    return uniquePathsHelper(n-1, m-1, obstacleGrid);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N + M)

int uniquePathsHelper(int row, int col, vector<vector<int>> &obstacleGrid, vector<vector<int>> &dp) {
    // If we encounter an obstacle at this cell, return 0
    if (row >= 0 && col >= 0 && obstacleGrid[row][col] == 1) {
        return 0;
    }
    
    // If we reach the top-left cell, we've found a valid path
    if (row == 0 && col == 0) {
        return 1;
    } 

    // If we go out of bounds, return 0
    if (row < 0 || col < 0) {
        return 0;
    }

    // If the result for this cell is already calculated, return it
    if (dp[row][col] != -1) {
        return dp[row][col];
    }

    // Calculate the number of paths by moving right and down
    int right = uniquePathsHelper(row, col - 1, obstacleGrid, dp);
    int down = uniquePathsHelper(row - 1, col, obstacleGrid, dp);

    // Store the result in the memoization table and return it
    return dp[row][col] = right + down;
}

// Main function for Approach 2
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size();
    int m = obstacleGrid[0].size();

    // Initialize a memoization table with -1 values
    vector<vector<int>> dp(n, vector<int>(m, -1));

    // Start the recursive calculation from the bottom-right cell
    return uniquePathsHelper(n-1, m-1, obstacleGrid, dp);
}

// Approach 3: Iterative dp
// Time Complexity: O(N * M)
// Space Complexity: O(N + M)

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size();
    int m = obstacleGrid[0].size();

    // Create a DP table to store the number of paths
    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Iterate through each cell in the grid
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (obstacleGrid[row][col] == 1) {
                dp[row][col] = 0; // If it's an obstacle, no paths
            }
            else if (row == 0 && col == 0) {
                dp[row][col] = 1; // Starting point, one path
            }
            else {
                int right = 0;
                int down = 0;

                // Calculate the number of paths by moving right and down
                if (col > 0) {
                    right = dp[row][col-1];
                }

                if (row > 0) {
                    down = dp[row - 1][col];
                }

                dp[row][col] = right + down; // Store the total paths
            }
        }
    }

    // Return the result for the bottom-right cell
    return dp[n-1][m-1];
}

// Approach 4: Space Optimization
// Time Complexity: O(N * M)
// Space Complexity: O(M)

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size();
    int m = obstacleGrid[0].size();

    // Initialize the previous row to store intermediate results
    vector<int> prevRow(m, 0);

    // Iterate through each row in the grid
    for (int row = 0; row < n; row++) {
        vector<int> currRow(m, 0);

        // Iterate through each cell in the row
        for (int col = 0; col < m; col++) {
            if (obstacleGrid[row][col] == 1) {
                currRow[col] = 0; // If it's an obstacle, no paths
            }
            else if (row == 0 && col == 0) {
                currRow[col] = 1; // Starting point, one path
            }
            else {
                int right = 0;
                int down = 0;

                // Calculate the number of paths by moving right and down
                if (col > 0) {
                    right = currRow[col - 1];
                }

                if (row > 0) {
                    down = prevRow[col];
                }

                currRow[col] = right + down; // Store the total paths
            }
        }

        // Update the previous row for the next iteration
        prevRow = currRow;
    }

    // Return the result for the bottom-right cell
    return prevRow[m-1];
}