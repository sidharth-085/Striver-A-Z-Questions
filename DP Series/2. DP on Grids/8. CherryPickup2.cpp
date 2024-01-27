#include <iostream>
#include <vector>
using namespace std;

// In this question, there are two friends starting from the top-left corner and top-right corner, 
// and a grid is given in which each cell contains some cherries. Both friends start from their positions 
// and try to collect the cherries. Find the maximum cherries both can pick together. If both reach a 
// cell at the same time, only one can pick the cherries.

// We are keeping 3 variable here row, col1 and col2 because at every step we will
// move to next row so one row variable is enough and for different directions
// we are keeping col1 and col2.

// Approach 1: Recursive Approach
// Time Complexity: O(3^N)
// Space Complexity: O(N)

int cherryPickupHelper(int row, int col1, int col2, int n, int m, vector<vector<int>> &grid) {
    // Check if either friend goes out of bounds
    if (col1 < 0 || col1 >= m || col2 < 0 || col2 >= m) {
        return INT_MIN;
    }

    // Check if both friends are at the last row
    if (row == n-1) {
        if (col1 == col2) {
            return grid[row][col1]; 
            // Only one friend can pick cherries at the same cell
        }
        else {
            return grid[row][col1] + grid[row][col2]; 
            // Both friends can pick cherries at different cells
        }
    }

    int maxi = INT_MIN;

    // Iterate through all possible moves for both friends
    // if first friend moves at one direction, other have 3 choices so total
    // choices for directions are 9 (3 x 3)

    for (int delta1 = -1; delta1 <= 1; delta1++) {
        for (int delta2 = -1; delta2 <= 1; delta2++) {
            int newCol1 = col1 + delta1; // move first friend
            int newCol2 = col2 + delta2; // then move second friend

            int findNext = cherryPickupHelper(row + 1, newCol1, newCol2, n, m, grid);
            // call recursion for getting max number of cherries picked by moving
            // in given direction for both friends

            maxi = max(maxi, findNext);
            // then, take the maximum one store in maxi variable
        }
    }

    // at last, if we are standing at same col (col1 == col2), means we have to
    // take current number of cherries only once and if not we have to take cherries
    // on different locations

    int maxCherries = -1;

    if (col1 == col2) {
        maxCherries =  maxi + grid[row][col1]; 
        // Only one friend can pick cherries at the same cell
    }
    else {
        maxCherries = maxi + grid[row][col1] + grid[row][col2]; 
        // Both friends can pick cherries at different cells
    }

    return maxCherries;
    // finally return the maximum cherries picked by both friends
}

int cherryPickup(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    return cherryPickupHelper(0, 0, m-1, n, m, grid);
}

// Approach 2: Memoization Approach (Faster than Iterative DP)
// Time Complexity: O(N * M * M)
// Space Complexity: O(N * M * M)

int cherryPickupHelper(int row, int col1, int col2, int n, int m, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp) {
    // Check if either friend goes out of bounds
    if (col1 < 0 || col1 >= m || col2 < 0 || col2 >= m) {
        return INT_MIN;
    }

    // Check if both friends are at the last row
    if (row == n-1) {
        if (col1 == col2) {
            return grid[row][col1]; // Only one friend can pick cherries at the same cell
        }
        else {
            return grid[row][col1] + grid[row][col2]; // Both friends can pick cherries at different cells
        }
    }

    if (dp[row][col1][col2] != INT_MIN) {
        return dp[row][col1][col2]; // If this subproblem is already computed, return it
    }

    int maxi = INT_MIN;

    // Iterate through all possible moves for both friends
    // if first friend moves at one direction, other have 3 choices so total
    // choices for directions are 9 (3 x 3)

    for (int delta1 = -1; delta1 <= 1; delta1++) {
        for (int delta2 = -1; delta2 <= 1; delta2++) {
            int newCol1 = col1 + delta1;
            int newCol2 = col2 + delta2;

            int findNext = cherryPickupHelper(row + 1, newCol1, newCol2, n, m, grid, dp);
            // call recursion for getting max number of cherries picked by moving
            // in given direction for both friends

            maxi = max(maxi, findNext);
        }
    }

    // at last, if we are standing at same col (col1 == col2), means we have to
    // take current number of cherries only once and if not we have to take cherries
    // on different locations

    int maxCherries = -1;

    if (col1 == col2) {
        maxCherries =  maxi + grid[row][col1]; 
        // Only one friend can pick cherries at the same cell
    }
    else {
        maxCherries = maxi + grid[row][col1] + grid[row][col2]; 
        // Both friends can pick cherries at different cells
    }

    return dp[row][col1][col2] = maxCherries; 
    // Memoize the result and return it
}

int cherryPickup(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, INT_MIN)));

    return cherryPickupHelper(0, 0, m-1, n, m, grid, dp);
    // first friend start from (0, 0) and other one starts at (0, m-1).
}

// Approach 3: Tabulation Method (Bottom Up DP)
// Time Complexity: O(N * M * M)
// Space Complexity: O(N * M * M)

int cherryPickup(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, INT_MIN)));

    // Initialize the last row of the DP table (base case)
    for (int col1 = 0; col1 < m; col1++) {
        for (int col2 = 0; col2 < m; col2++) {
            if (col1 == col2) {
                dp[n-1][col1][col2] = grid[n-1][col1]; 
                // Only one friend can pick cherries at the same cell
            }
            else {
                dp[n-1][col1][col2] = grid[n-1][col1] + grid[n-1][col2]; 
                // Both friends can pick cherries at different cells
            }
        }
    }

    // Fill in the DP table from the second-to-last row to the first row
    for (int row = n-2; row >= 0; row--) {
        // in bottom up dp, row starts from n-2 and ends at 0.

        for (int col1 = m - 1; col1 >= 0; col1--) {
            // in bottom up dp, col1 starts from m - 1 and ends at 0.

            for (int col2 = 0; col2 < m; col2++) {
                // in bottom up dp, col2 starts from 0 and ends at m - 1.

                int maxi = INT_MIN;

                // Iterate through all possible moves for both friends
                for (int delta1 = -1; delta1 <= 1; delta1++) {
                    for (int delta2 = -1; delta2 <= 1; delta2++) {
                        int newCol1 = col1 + delta1;
                        int newCol2 = col2 + delta2;

                        // if newCols are going out of bounds, dont take them
                        // (out of bounds base case)
                        if (newCol1 < 0 || newCol1 >= m || newCol2 < 0 || newCol2 >= m) {
                            continue;
                        }

                        // finally take the maximum number of cherries for next paths

                        int findNext = dp[row + 1][newCol1][newCol2];
                        maxi = max(maxi, findNext);
                    }
                }

                // at last, if we are standing at same col (col1 == col2), means we have to
                // take current number of cherries only once and if not we have to take cherries
                // on different locations

                int maxCherries = -1;

                if (col1 == col2) {
                    maxCherries = maxi + grid[row][col1]; 
                    // Only one friend can pick cherries at the same cell
                }
                else {
                    maxCherries = maxi + grid[row][col1] + grid[row][col2]; 
                    // Both friends can pick cherries at different cells
                }

                dp[row][col1][col2] = maxCherries; 
                // Fill in the DP table with the result
            }
        }
    }

    return dp[0][0][m-1]; 
    // return the dp element, row starts from 0, col1 from 0 and col2 from m-1.
}

// Approach 4: Space Optimization (Bottom Up DP)
// Time Complexity: O(N * M * M)
// Space Complexity: O(M * M)

int cherryPickup(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> nextRow(m, vector<int>(m, INT_MIN));
    // keep 2-D Dp for carrying col1 and col2 values which is nextRow (row + 1).
    // just replace dp[row + 1][col1][col2] with prevRow[col1][col2] and
    // dp[row][col1][col2] with currRow[col1][col2]

    // Initialize the last row of the DP table (base case)
    for (int col1 = 0; col1 < m; col1++) {
        for (int col2 = 0; col2 < m; col2++) {
            if (col1 == col2) {
                nextRow[col1][col2] = grid[n-1][col1]; 
                // Only one friend can pick cherries at the same cell
            }
            else {
                nextRow[col1][col2] = grid[n-1][col1] + grid[n-1][col2]; 
                // Both friends can pick cherries at different cells
            }
        }
    }

    // Fill in the DP table from the second-to-last row to the first row
    for (int row = n-2; row >= 0; row--) {
        // in bottom up dp, row starts from n-2 and ends at 0.

        vector<vector<int>> currRow(m, vector<int>(m, INT_MIN));
        // currRow Dp for carring diff values of col1 and col2 and update nextRow
        // after every row.

        for (int col1 = m - 1; col1 >= 0; col1--) {
            // in bottom up dp, col1 starts from m - 1 and ends at 0.

            for (int col2 = 0; col2 < m; col2++) {
                // in bottom up dp, col2 starts from 0 and ends at m - 1.

                int maxi = INT_MIN;

                // Iterate through all possible moves for both friends
                for (int delta1 = -1; delta1 <= 1; delta1++) {
                    for (int delta2 = -1; delta2 <= 1; delta2++) {
                        int newCol1 = col1 + delta1;
                        int newCol2 = col2 + delta2;

                        // if newCols are going out of bounds, dont take them
                        // (out of bounds base case)
                        if (newCol1 < 0 || newCol1 >= m || newCol2 < 0 || newCol2 >= m) {
                            continue;
                        }

                        // finally take the maximum number of cherries for next paths

                        int findNext = nextRow[newCol1][newCol2];
                        maxi = max(maxi, findNext);
                    }
                }

                // at last, if we are standing at same col (col1 == col2), means we have to
                // take current number of cherries only once and if not we have to take cherries
                // on different locations

                int maxCherries = -1;

                if (col1 == col2) {
                    maxCherries = maxi + grid[row][col1]; 
                    // Only one friend can pick cherries at the same cell
                }
                else {
                    maxCherries = maxi + grid[row][col1] + grid[row][col2]; 
                    // Both friends can pick cherries at different cells
                }

                currRow[col1][col2] = maxCherries; 
                // Fill in the DP table with the result
            }
        }

        nextRow = currRow;
    }

    return nextRow[0][m-1]; 
    // return the dp element, row starts from 0, col1 from 0 and col2 from m-1.
}